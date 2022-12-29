## RDBMS vs file system
- Data is relational
- Data is large and needs to be queried quickly
- DB is easier to insert a new column
- DB is easier to search due to an index being created
- Easier to delete a row in a DB
- Easier to sort in a DB
- DB is good when users read/write the same kind of data all the time
- DB is better for atomic transactions
- File system is limited to OS implementation
### In summary
- lots of data
- data is related
- data is similar
- lots of lookup

## SQLite game idea
- Game manager maintains a database of all the game events, including events that occurred in previous sessions.
- Player can ask questions of the database (create queries)
- Core gameplay is that the player forms SQL-like queries using game-like objects and sends these queries to the game manager itself.
- Player has three main kinds of actions: asking questions and taking actions and moving.
- A player action either inserts data into the database, updates it or deletes a row.
- Player's initial power is a select
- Actor properties are stored in db e.g enemy type, enemy element, damage e.t.c
- Rpgmaker's DB is an example

### SQLite specialties
- Each SQLite db is a file
- 
