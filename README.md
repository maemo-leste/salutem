# salutem
greeter app for mameo leste

this application displays /usr/share/salutem.html when run and then stores its md5 sum in ~/.config/salutem-ran
if the md5 sum of /usr/share/salutem.html is allready the same as the one in ~/.config/salutem-ran it simply exits

usage: salutem -o -t <path to html file>
