#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Description:
This application calculates the housing allowance for a single pensioner
for years 2024 and 2025 as interest-free assets vary.

Applcation name:
elsaajan_asumistukilaskuri.c

Compile application in Ubuntu:
gcc elsaajan_asumistukilaskuri.c -o elsaajan_asumistukilaskuri

Run application in Ubuntu:
./elsaajan_asumistukilaskuri
*/

void laske_asumistuki
  (
    float _saasto, float _elakkeet, float _tulo_raja, float _var_raja, 
    float _perusomavastuu_per_kk, float _vuokra, float _vesi, char* str_vuodelle,
    float _vuositulokerroin, float _lisaomavastuukerroin, float _astukikerroin  
  )
{
  // Lasketaan eläkkeensaajan asumistuki
  float saasto = _saasto;
  printf("saasto = %.2f vuodelle %s \n", saasto, str_vuodelle);

  // saastosta voidaan vähennetään 2000€ vuosina 2024 ja 2025
  saasto -= 2000.0;

  // kaikki bruttoeläkkeet summattuina
  float elakkeet = _elakkeet;
  printf("elakkeet = %.2f \n", elakkeet);

  // varallisuusraja 
  float var_raja = _var_raja; // vuonna 2024 18306.0 - 2025 15000

  float vuositulo = (elakkeet * 12.0) + (saasto - var_raja) * _vuositulokerroin; // vuonna 2024 0.08 
  float kk_tulo = vuositulo / 12.0; // 12 kk

  // Kelan kielessa tulo_raja on lisäomavastuun tuloraja
  float tulo_raja = _tulo_raja; // v 2024 10280.0 - v 2025?
  float perusomavastuu_per_kk = _perusomavastuu_per_kk;   //v 2024 56.78
  float lisaomavastuu_per_v = 0.0;      // lasketaan
  float lisaomavastuu_per_kk = 0.0;     // lasketaan

  // Lisäomavastuu maaraytyy mikäli laskennallinen vuositulo ylittää
  // 10280 rajan vuonna 2024 -mikä on tuo luku vuodelle 2025.
  if ( (vuositulo - tulo_raja) > 0.0 ) {
    lisaomavastuu_per_v = (vuositulo - tulo_raja) * _lisaomavastuukerroin; // v 2024 0.413; // prosenttiluku loytyy laista
    lisaomavastuu_per_kk = lisaomavastuu_per_v / 12.0;
  }

  //asumistuki = ( (vuokra + vesi) - (perusomavastuu_per_kk + lisaomavastuu_per_kk)) * 0.85
  float astuki_per_kk = ((_vuokra + _vesi) - (perusomavastuu_per_kk + lisaomavastuu_per_kk)) * _astukikerroin; // v 2024 0.85;

  // pyoristys 2:een desimaaliin - hiukan oudosti tehdaan dartissa!
  printf("Eläkkeensaajan asumistuki %s \n", str_vuodelle);
  printf("%.2f \n", astuki_per_kk);
  //print(""); // empty line
}
void
main (int argc, char **argv)
{
  for (float saasto = 5000.0; saasto < 95000.0; saasto += 5000.0) {
    laske_asumistuki
    (
      saasto, 1076.0, 10280.0, 18306.0,
      56.78, 512.0, 20.0, "2024",
      0.08, 0.413, 0.85
    );
  }

  // huomaa muuuttuneet vakiot ja kertoimet vuodesta 2024.
  for (float saasto = 5000.0; saasto < 95000; saasto += 5000) {
    laske_asumistuki
    (
      saasto, 1091.0, 10280.0, 15000.0,
      56.78, 512.0, 20.0, "2025",
      0.15, 0.435, 0.85
    );
  }
}


