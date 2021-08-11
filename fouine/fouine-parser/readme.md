# fouine-parser

This is the parser of the fouine language. It's aim is to provide an ast to the fouine parser.

# syntax

The fouine description langage is quite simple and describe some object.

# feature

- Allow you to administrate your different servers...
    - on prime servers
    - docker
    - docker-compose ??
    - virtual servers ?
    - gcp
    - amazon
    - ovh cloud

- apply fouine source to IT.
- dump fouine source for IT.
- diff system and fouine source.
- keep history of your system.
- update fouine source and reaply
- keep informed of system not up2date.

- list / add / remove services for fouine instance

# fouine grammar :

## basic type
### Host
properties : 
os : Windows, Linux, MacOsX, Debian, Ubuntu...
version : 
name : 
address :
port : optional ?
list<packages> = []
events: up, done, load, diskfull,... => {
}


# fouine standard library :

#


