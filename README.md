# salutem
Greeter application for Maemo Leste

This application will display /usr/share/salutem.html when run and stores its MD5 sum in ~/.config/salutem-ran after displaying.

If the MD5 sum of /usr/share/salutem.html is already the same as the one in ~/.config/salutem-ran it directly exits. Else it will display the new .html.

Usage: salutem -o -t \<path-to-html-file\>
