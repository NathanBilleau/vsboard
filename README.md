# vsboard

## Installer NodeJS
``` bash
pi@raspberrypi:~ $ sudo apt-get install node
```

### La version de nodeJS ne fonctionnera pas pour notre cas. Il faut donc la mettre à jour :
``` bash
pi@raspberrypi:~ $ sudo apt-get update && sudo apt-get upgrade
pi@raspberrypi:~ $ wget http://node-arm.herokuapp.com/node_latest_armhf.deb
pi@raspberrypi:~ $ sudo dpkg -i node_latest_armhf.deb
```

### Vérifiez la version de NodeJS, elle doit être au minimum à 4.2.1 :
``` bash
pi@raspberrypi:~ $ node -v
v4.2.1
```

## Installer le serveur web et la page web
``` bash
pi@raspberrypi:~ $ git clone https://github.com/NathanBilleau/vsboard
pi@raspberrypi:~ $ cd vsboard-master/WEB/
pi@raspberrypi:~/vsboard-master/WEB $ node index.js
http://localhost:5555/
```


**Ip Raspberry : 172.18.49.245**

Adresse du serveur web : **http://<IP_Raspberry>:5555/**



