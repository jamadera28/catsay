# catsay
A fan imitation of apt's popular cowsay, using cats

All ASCII cats were obtained from https://www.asciiart.eu/animals/cats

## Usage
Pass text to the program using any standard input method and the program with output that text in a speech bubble being spoken by one of three ASCII cats picked at random

Using option `-w <1,2,3>` will specify __which__ cat you see, otherwise the cat you see is psuedorandomly chosen using C's rand() function from stdlib.h
  
### Sample runs
`$ fortune | ./catsay`...  _`fortune` can be installed with `sudo apt install fortune`_

 __________________________________________________________

/                                                          \

| But, for my own part, it was Greek to me.                |

|               -- William Shakespeare, "Julius Caesar"    |

\__________________________________________________________/
          
          \           /)
           
           \  /\___/\ ((
              
              \`@_@'/  ))
              
              {_:Y:.}_//

hjw ----------{_}^-'{_}----------

`$ date | ./catsay -w 2`

`$ ./catsay -w 2 < words.txt`
