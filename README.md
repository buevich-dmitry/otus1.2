To download and install the latest version, run:
```
wget -O helloworld-Linux.deb https://github.com/buevich-dmitry/otus1.2/releases/latest/download/ip_filter-Linux.deb
sudo dpkg -i ip_filter-Linux.deb
```

Also you can build the project locally:
```
./build.sh
sudo dpkg -i bin/ip_filter-*-Linux.deb
```

Then run helloworld app:
```
ip_filter
```
