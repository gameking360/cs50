select avg(rating) from movies inner join ratings on movie_id = id
where year = 2012;
