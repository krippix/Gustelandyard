# Gustelandyard
Attempting to Build the boardgame Scotland Yard in C++
After I manage to implement the game logic, I will think about how to create a frontend for it.
Having it as a command-line game doesent really make sense, as the positions of Mr. X is easily visible this way.

I am not yet sure whether it will be as a webapp or as an actual downloadable client.

## ToDo list
- [x] Implement Players
- [x] Implement Map
- [x] Implement Locations
- [x] Implement Basic Game logic
- [x] Implement ticket usage (and the requirement)
- [x] Add win-condition "no detective can move"
- [x] Implement announcement of Mr.X position
- [ ] Implement 2x Ticket (Including correct pathing history!) (Maybe as 0-turn)
- [ ] Check input map for redundant vertices, or handle them at least
- [ ] Prevent wrong inputs
- [x] Fix CLI selection list when unavailable spots are displayed
- [ ] Implement Multiple Map support
- [ ] Implement Dummy-Players (if less than 3 detectives)

- [ ] Create Frontend (oof)