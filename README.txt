The dataset is created in dataset.cpp file. 
Just executing it creates a 3.94GB file (for 10M vectors)
with "vector_file.txt" filename.

The data is then read from the file and 
the kd tree is built dynamically in the 
Building_tree_and_query_search.cpp file.

This also creates 100 queries at random(following Gaussian dist.)
calculates the median time required for the searches.


Dynamically_creating_dataset.cpp creates everything
together and dynamically. Its the whole code in one place.
