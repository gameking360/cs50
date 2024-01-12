select count(title) from movies inner join ratings on movie_id = id where rating = 10;
