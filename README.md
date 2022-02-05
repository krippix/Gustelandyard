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
- [x] Tie Mr. X announcements to his turn instead of the game turn. (This is why 24 "turns" happen in the first place)
- [x] Implement 2x Ticket (Including correct pathing history!) (Maybe as 0-turn)
- [x] Fix CLI selection list when unavailable spots are displayed
- [ ] Implement multi-Map support
- [ ] Create Frontend (oof)

- [ ] Implement Dummy-Players (if less than 3 detectives)

# "Documentation"
## Map importing
The Maps in the game are planned to be folders, containing the visual implementation (of which I currently have no idea how to implement), and a json file describing the map as graph.

There are four vehicle types, in the follwing order: taxi, bus, train, boat
