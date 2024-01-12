select title from movies where id in(
    select movie_id from stars inner join people on id = person_id and name = "Johnny Depp"
) and id in (
    select movie_id from stars inner join people on id = person_id and name = "Helena Bonham Carter"
);
