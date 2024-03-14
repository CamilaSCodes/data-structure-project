# Data Structure Project

## A functional National Telephone and Address Directory System fully written in C

This project was undertaken as a component of the Data Structure course, implemented as an Abstract Data Type and using three Data Structures:
* AVL Tree: Each tree has a root node that stores a unique Brazilian area code (DDD). Duplicate area codes are not allowed. Every child node within the tree stores an 8-digit telephone number associated with that DDD, along with the respective user name and address;
* Linked List: Each node in the list stores a memory address of a Tree, allowing fast access to the data;
* Hash Table: Each slot of the Hash Table points to a Linked List. enabling efficient retrieval of information within the structure.

#### Features: 
* Insertion of a user into the chosen DDD, preventing repetition of names and phone numbers. If repetition occurs, the system suggests three available numbers that have not been utilized yet;
* Removal of a user from the selected DDD, displaying the heights of both trees (sorted by phone number and name) before and after the removal;
* Finding a user within the chosen DDD based on the provided phone number, and displaying all relevant information;
* Displaying all users from the selected DDD, performing all three available traversal techniques to search the Tree; 
* Displaying the complete directory by DDD, sorted by phone number and name.

In addition to the code, the repository includes a PDF report providing comprehensive information and explanations about the developed program. This report elucidates the utilized structures and functions, detailing the rationale behind their incorporation at each developmental stage.
