# Foobar


## Usage

```c++
std::vector<float> c = {3, 4, 5, 0, 0, 0};
std::vector<float> b = {-5,-6};
std::vector<std::vector<float>> a;
a.push_back({-1,-2,-3,1,0});
a.push_back({-2,-2,-1,0,1});


LPModel model{a, b, c, std::vector<float>(5,0)};
model.doSimplex();
printVec(model.X);
printVec(model.basisIdx);
printVec(model.nonbasisIdx);
```

## License
[MIT](https://choosealicense.com/licenses/mit/)