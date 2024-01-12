select title from movies m inner join stars s on s.movie_id = m.id inner join ratings r on r.movie_id = m.id join people p on p.id = s.person_id where p.name = "Chadwick Boseman"
order by r.rating desc limit 5;
