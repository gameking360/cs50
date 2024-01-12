import os
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify, json
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    actions = db.execute("SELECT actionName, SUM(qtdAction) as qtdAction from actions where user_id = ? and type_action = ? group by actionName",session["user_id"],"Buy")
    venda = db.execute("SELECT actionName, SUM(qtdAction) as qtd from actions where user_id = ? and type_action = ? group by actionName",session["user_id"],"Sell")

    if(len(actions) == len(venda)):
        for i in range(len(actions)):
            actions[i]["qtdAction"] -= venda[i]["qtd"]

    total = 0

    for action in actions:
        action["precoAgora"] = lookup(action["actionName"])["price"]

        action["Total"] = float(action["precoAgora"]) * float(action["qtdAction"])
        total += float(action["Total"])

    user = db.execute("SELECT username as name, cash as money from users where id = ?",session["user_id"])
    user[0]["Total"] = total + user[0]["money"]


    return render_template("index.html",actions = actions,user = user[0])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method =="GET":
        return render_template("buy.html")
    else:
        preco = float(request.form.get('finalPrice'))
        dinero = db.execute("select CASH from users where id = ?",session["user_id"])

        if preco > float(dinero[0]["cash"]):
            return apology("Você não tem dinheiro suficiente para a ação", 500)
        db.execute("INSERT INTO actions (user_id,actionName, qtdAction,priceEpoca,date, type_action) values(?,?,?,?,?,?)", session["user_id"],
                   request.form.get("symbol"),int(request.form.get("shares")), float(request.form.get("finalPrice")),
                   datetime.now(), "Buy")
        db.execute("UPDATE users SET cash = ? where id = ?",float(dinero[0]["cash"]) - preco, session["user_id"])
        return redirect("/")


@app.route("/validate",methods=["GET"])
@login_required
def validate():
    ee = lookup(request.args.get("symbol"))
    return ee

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    historico = db.execute("SELECT actionName as action, qtdAction as qtd, priceEpoca as price, date, type_action from actions where user_id = ?",
                           session["user_id"])

    return render_template("history.html", historico = historico)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")



@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html",lookup = "")

    elif request.method == "POST":

        ee = lookup(request.form.get("symbol"))
        if ee == None:
            return apology("Not found", 400)
        return render_template("quote.html", lookup = ee)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if request.form.get("username") in  [None,""," "] or request.form.get("password") in [""," ",None] or request.form.get("confirmation") in [""," ",None]:
            return apology("Error", 400)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Error",400)
        db.execute("INSERT INTO users(username,hash) values (?,?)",request.form.get("username"),generate_password_hash(request.form.get("password")))
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct

        if len(rows) != 0 :
            for user in rows:
                if check_password_hash(user["hash"],request.form.get("password")):
                     # Remember which user has logged in
                    session["user_id"] = rows[0]["id"]

                    # Redirect user to home page
                    return redirect("/")

        return apology("invalid username and/or password", 403)


    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        acoes = db.execute("select actionName as name, sum(qtdAction) as max from actions where user_id = ? and type_action = ? group by name", session["user_id"],"Buy")
        vendas = db.execute("select actionName as name, sum(qtdAction) as max from actions where user_id =  ? and type_action = ? group by name",session["user_id"],"Sell")

        for i in range(len(acoes)):
            acoes[i]["max"] -= vendas[i]["max"]

        return render_template("sell.html", acoes = acoes)

    else:
        db.execute("INSERT into actions (user_id,actionName,qtdAction,priceEpoca,date,type_action) values (?,?,?,?,?,?)", session["user_id"],request.form.get("symbol"),
                   int(request.form.get("shares")),float(lookup(request.form.get("symbol"))["price"] * float(request.form.get("shares"))),
                   datetime.now(),"Sell")

        db.execute("Update users set cash = cash + ? where id = ?", float(lookup(request.form.get("symbol"))["price"] * float(request.form.get("shares"))),session["user_id"])
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
