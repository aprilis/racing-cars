Raport dostępny jest w pliku [Raport.ipynb](Raport.ipynb)

# Instalacja

## 1. Zależności

Potrzebny jest kompilator z obsługą c++17

Dodatkowe biblioteki:

```
sudo apt install libeigen3-dev libsfml-dev libarmadillo-dev libtbb-dev cmake
```

Instalacja [PAGMO 2.0](https://esa.github.io/pagmo2):

```
git clone https://github.com/esa/pagmo2.git
cd pagmo2
mkdir build
cd build
cmake .. -DPAGMO_WITH_EIGEN3=ON
make
sudo make install
```

## 2. Kompilacja
```
mkdir build
cd build
cmake ..
make
```

## 3. Uruchomienie

* Uczenie: uruchom jeden z eksperymentów (`DNN_NSGA2`, `DNN_20_NSGA2`, `DNN_20_NSGA2_multi`), żeby zobaczyć listę argumentów. W `DNN_20_NSGA2_multi` parametr `population path` może przyjmować albo wartość `random` by zacząć od losowej populacji, albo ścieżkę do pliku z wyeksportowaną populacją z poprzedniego uczenia.
* Wizualizacja: uruchom odpowiedni program (`DNN_vis` dla populacji wytrenowanych skryptem `DNN_NSGA2`, `DNN_20_vis` dla pozostałych) z parametrami `<sciezka_do_mapy> <sciezka_do_populacji> <limit_czasu>` np. ```./DNN_20_vis ../maps/trasa1.png population/DNN_NSGA_2L_XXXX_YYYYYY 30```
* Testowa gra (strzałkami): ```./TestGame <sciezka_do_mapy>```
