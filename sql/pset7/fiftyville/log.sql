-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find ocorrence
select * from crime_scene_reports where year = 2020 and month = 7 and day = 28 and street = 'Chamberlin Street';

-- Check transation
select p.name, amount, transaction_type from atm_transactions a inner join bank_accounts b on b.account_number = a.account_number
inner join people p on p.id = b.person_id
where a.atm_location = 'Fifer Street' and a.transaction_type = 'withdraw' order by p.name;


select * from atm_transactions where atm_location = 'Fifer Street';

-- Check intervies
select * from interviews where year = 2020 and month = 7 and day = 28 and transcript like '%courthouse%';

-- Phone calls

select * from phone_calls p inner join people a on p.phone_number = a.phone_number where a.name='Louis';

-- logs

select p.name, c.activity, c.day,c.hour,c.minute from courthouse_security_logs c inner join people p on c.license_plate = p.license_plate where year = 2020 and month = 7 and day = 28 order by name;


-- Acount
select * from bank_accounts where person_id in (
    select p.id from courthouse_security_logs c inner join people p on c.license_plate = p.license_plate where year = 2020 and month = 7 and day = 28 order by name
);


--Eugene , após sair viu a pessoa fazendo 3 saques de dinheiro
-- Raymond ouviu o criminoso fazendo a ligação para pegar o avião, ligação durou menos de 1 minuto
-- Ruth dentro de 10 minutos depois do roubo viu o criminoso sair

--
select
