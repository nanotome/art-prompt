# User flow
1. app bundle contains an sqlite file that stores all the svg strings (one svg per row)
2. user starts app
3. app selects a random row from the sqlite svg table. See: https://stackoverflow.com/a/2279723/2259144
4. svg file is rendered


## Extra
5. if user presses F, the next random row is selected
6. if user presses D, the row is marked as done and will not be selected again


### Loading SVG into SDL:
[StackOverflow](https://stackoverflow.com/a/64838399/2259144)
```c++
const std::string svg =
    "<svg height='512' width='512'><circle cx='256' cy='256' r='256' stroke='red' stroke-width='4' fill='red'/></svg>";

  SDL_RWops *rw = SDL_RWFromConstMem(svg.c_str(), svg.size());
  SDL_Surface *surface = IMG_Load_RW(rw, 1);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
```

### Select random row from sqlite
[StackOverflow](https://stackoverflow.com/a/2279723/2259144)
```sql
SELECT * FROM table ORDER BY RANDOM() LIMIT 1;
```

# TODO
- [ ] Test SDL2 svg load
- [ ] Create C++ script to write all the twemoji SVG into an sqlite db
- [ ] Load sqlite in program and select random row
