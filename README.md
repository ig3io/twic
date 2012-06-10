Twic
====
Twitter search in your console. In C.

Development stage
-----------------
I've just started this miniproject. It's in a very, very, early stage of development.

Firts time using the Twitter API!

Use
---
    ./twic <search term URL friendly 1> ...  <search term URL friendly N> <max tweets>

It will print one line for each tweet found with the following structure:

    <user name>: <tweet text>

**WARNING:** Twic still doesn't know how to deal with large responses from twitter, neither it has error handling. Work in progress. If you use more than one search term, use a low *<max tweets>* number.

Compiling
---------
    cd <path to twic>
    make

Dependencies
------------
* [cJSON][1]
* libcurl installed

License
-------
* Code of my own under the MIT License. See LICENSE for more details.
* For cJSON license, see cJSON.h or cJSON.c for its legal notice.

[1]: http://sourceforge.net/projects/cjson/
