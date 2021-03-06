# --- OOP-projects ---
Few C++/Qt projects I worked on during the 2nd year course for Object Oriented Programming


## Norven Turrets
App monitoring the turrets of the castle, it has two modes:
- Watch Officer: adds/updates/removes turrets (+ undo/redo)
- Watchman: views the turrets one by one, saves in his catalogue what he wants / views the catalogue / filter functionality (+ undo/redo)  
Each of the 2 lists (all turrets/saved turrets) can be configured(settings.txt) to be kept in memory/txt file/csv file/html table

## Constellations
Astronomers app (using Model-View)
Given a list of astronomers and the constellation they study, the app opens a window for each astronomer, displaying all the stars. Each astronomer can:
- filter the stars to see only his constellation
- add a new valid star
- search a star by name (find matches as he types)

## Testers & Programmers
(using Observer Pattern)  
The app recieves a list of programmers/testers and opens a window for each, with a list of issues (name | status | reporter | solver)
- a tester can add a new found issue
- a programmer can resolve an open issue (solver will be updated as his name)
- both can remove only closed issues

## Illnesses
App that keeps a list of illnesses, their category and their symptoms. User can:
- see the symptoms of an illness
- search by category
