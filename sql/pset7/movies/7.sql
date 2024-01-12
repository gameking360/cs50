select title, r.rating from movies inner join ratings r on r.movie_id = id where year = 2010 order by r.rating desc, title;
