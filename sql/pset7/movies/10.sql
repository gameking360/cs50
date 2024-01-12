select name from people where id in (
    select person_id from directors where movie_id in
    (
        select m.id from movies m inner join ratings r on m.id = r.movie_id where r.rating >= 9.0
    )
);
