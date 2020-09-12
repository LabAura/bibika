1.Заходим на www.raspberrypi.org в раздел Download. Выбираем raspbian. Выбираем Raspbian Stretch Light Download ZIP.
2.Разархивируем.
3.Полученный образ записываем на SD-карту с помощью Win32DiskImager.exe
4.Устанавливаем карту в стенд. Запускаем.
5.Заходим под пользователем pi с паролем raspberry.
6.Задаём сетевые реквизиты.
        nano /etc/dhcpcd.conf
  Находим строки в конце файла
        # Example static IP configuration
        #interface eth0
        #static ip_address=192.168.1.23/24
        #static ipv6_addresss=fd54::1/64
        #static ip_routers=192.168.1.1
        #static domain_name_servers=192.168.1.1 8.8.8.8
  и приводим их к виду:
        # Example static IP configuration
        interface eth0
        static ip_address=10.13.5.116/24
        #static ipv6_addresss=fd54::1/64
        static ip_routers=10.13.5.1
        static domain_name_servers=10.0.20.2 10.0.20.4
  Нажимаем Ctrl+X для выхода и Y, а затем Enter для сохранения сделаных изменений.
7.Перезагружаем систему
        reboot
  На этом этапе должен стоять нужный IP-адрес, при загрузке должно вывести IP-адрес перед приглашением ко входу в систему.
  Если IP-адрес отличается от того, что задавался в файле, то стоит проверить файл.
8.Скачиваем и устанавливаем обновления.
        sudo apt update && sudo apt upgrade -y
9.Настройка локалей (языковых параметров).
        sudo dpkg-reconfigure locales
  С помощью пробела отмечаем/удаляем локали. Нужно, чтобы в итоге осталось только две локали "en_US.UTF-8 UTF-8" и "ru_RU.UTF-8 UTF-8"
  и нажимаем Enter. После вылезет окошко, в котором нужно будет выбрать локаль по-умолчанию ru_RU.UTF-8.
10.Установка временной зоны.
        sudo timedatectl set-timezone Asia/Yekaterinburg
11.Смена раскладки с Британской на Американскую.
        sudo dpkg-reconfigure keyboard-configuration
  В появившемся окошке нажимаем Enter, чтобы выбрать пункт по-умолчанию "Generic 105-key (Intl) PC"
  После в новом окошке выбираем пункт "Other" в самом низу, затем ищем пункт "English (US)", и после выбираем "English (US)" в самом верху.
  Во всех последующих окошках нажимаем Enter.
12.Устанавливаем и добавляем в автозагрузку VNC и SSH.
  Устанавливаем VNC.
         sudo apt install realvnc-vnc-server -y
  Добавляем VNC и SSH в автозагрузку.
         sudo systemctl enable vncserver-virtuald ssh
         sudo systemctl start vncserver-virtuald ssh
13.Активируем 1-wire, I2C, SPI.
  Заходим в raspi-config.
         sudo raspi-config
  Заходим в пункт "5 Interfacing Options", затем по очереди выбираем пункты "P4 SPI", "P5 SPI" и "P7 1-wire" и в каждом выбираем Yes.
14.Перезагружаемся.
         reboot
15.Устанавливаем графический сервер Xserver-xorg.
         sudo apt install --no-install-recommends xserver-xorg -y
16.Ставим графическую оболочку Raspbian Pi Desktop (RPD).
         sudo apt install raspberrypi-ui-mods -y
17.Перезагружаемся и заходим в систему по пользователем pi с паролем raspberry.

Далее, консольные команды выполняются в эмуляторе терминала Termit. Он вызывается клавишесочетанием Ctrl+Alt+T.

18.Настройка раскладки клавиатуры.
  Нажимаем правой кнопкой мыши на Панель задач (вверху) в любом свободном месте. Выбираем "Добавить/Убрать элементы списка".
  Нажимаем "Добавить" и ищем в списке "Обработчик раскладки клавиатуры", выбираем его и нажимаем "Добавить", а затем "ОК".
  На правой панели появляется значок флага, это переключатель.
  Нажимаем по нему правой кнопкой мыши, выбираем пункт "Обрабочик клавиатуры Settings".
  Снимаем галочку "Сохранить системные раскладки".
  В разделе "Раскладки клавиатуры" нажимаем "Добавить". Из появившегося списка выбираем "ru Русская" и нажимаем "ОК".
  Затем выходим, нажав "X" вверху слева.
  
  Далее требуется отредактировать файл конфигруации среды. Вызываем Termit, нажав Ctrl+Alt+T и выполняем команду.
         nano .config/lxpanel/LXDE-pi/panels/panel
  Ищем в самом конце файла раздел Plugin и в нём изменяем строчки:
         LayoutsList=us меняем на LayoutsList=us,ru
         ToggleOpt=grp:alt_shift_toggle
  И добавим строчку
         KeepSysLayouts=0
  Сохраняем файл "Ctrl+X", затем "Y" и Enter.
19.Настройка автоматического входа пользователя pi.
  Выполним команду в терминале
       sudo sed -i -e "s/^\(#\|\)autologin-user=.*/autologin-user=pi/" /etc/lightdm/lightdm.conf
  Потом следует перезагрузиться.
  После перезагрузки система не должна спросить данные для входа, и настройки для раскадки клавиатуры должны примениться
  (должны быть 2 языка и переключение между ними через клавиши Shift+Alt).
20.Установим среду программирование Geany.
       sudo apt install geany -y
21.Установим утилиты работы с GitHub.
       sudo apt install git-core -y
22.Установим библиотеку работы с GPIO. В терминале.
       cd
       git clone git://git.drogon.net/wiringPi
       cd wiringPi
       ./build
  Проверим работу библиотеки. Посмотрим версию и выведем все пины GPIO.
       gpio -v
       gpio readall
23.Установим библиотеку bcm2835.
       cd
       wget http://www.open.com.au/mikem/bcm2835/bcm2835-1.3.tar.gz
       tar -xzvf bcm2835-1.3.tar.gz
       cd bcm2835-1.3
       ./configure
       make
       sudo make install
24.Скачаем библиотеки, необходимые для работы со стендом.
       cd
       git clone http://github.com/Lab305/practic.git
       cd practic
  Скомпилируем библиотеки.
       make
25.Скопируем файлы библиотек по системным папкам.
       sudo cp libAura.a /usr/lib/
       sudo cp Aura.h /usr/include/
       sudo cp AuraLib.py /usr/lib/python2.7/
26.Проверим работу библиотек.
  Отроем Geany и нажимаем клавишесочетание "Ctrl+S", чтобы сохранить файл. Файл называем test.c 
  Затем нажимаем по вкладке "Сборка", выбирем пункт "Установить команды сборки" и редактируем строчки до следующего состояния:
       gcc -Wall -c "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread
       gcc -Wall -o "%e" "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread
  Теперь напишем программу:
       #include <stdio.h>
       #include <Aura.h>
       int main () {
           printf("%f",get_temp());
       }
  Скомпилируем, собирём и запустим программу. В эмуляторе терминала должна вывестись температура с датчика температуры.
27.Установим утилиты dnsmasq и hostapd
       sudo apt install dnsmasq hostapd -y
28.Подготовим интерфейс беспроводной сети. Зайдём в файл /etc/dhcpcd.conf.
       nano /etc/dhcpcd.conf
  Допишем в конец строчки:
       interface wlan0
       static ip_address=192.168.4.1/24
       nohook wpa_supplicant
29.Настроим DHCP-сервер.
  Сохраняем оригинальный файл dnsmasq.conf
       sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
  Скачиваем каталог со всеми конфигурационными файлами и настройками.
       cd
       git clone https://github.com/Lab305/bibika.git
       cd bibika
  Копируем файл готовый dnsmasq.conf.
       sudo cp dnsmasq.conf /etc/
30.Настройка точки доступа WIFI.
  Копируем файлы из папки hostapd в папку с настройками точки доступа
       sudo cp hostapd/* /etc/hostapd/
31.Подключим конфигурационный файл hostapd.conf
  Копируем файл hostapd (1) в директорию /etc/default/
       sudo mv hostapd\ \(1\) /etc/default/hostapd
32.Добавим службы dnsmasq и hostapd в автозагрузку.
       sudo systemctl enable dnsmasq hostapd
33.Переместим программы работы с бибикой и камерой.
       cd
       mv bibika/car/* ./
34.Настроим работу камеры.
       sudo raspi-config
  Выбираем "5 Interfacing Options", затем "Camera", затем "Да".
35.Перезагружаемся для применения настроек сетевых реквизитов для WiFi.
       reboot
36.Проверяем настройку сетевых реквизитов.
       ip -c a
  Должны вывестись 3 интерфейса, один из которых wlan0 с адресом 192.168.4.1
39.Изменим команды сборки для программы.
  Отроем в Geany файл server.cpp по пути /home/pi/server.cpp и изменим команды сборки на следующие:
       g++ -Wall -c "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread
       g++ -Wall -o "%e" "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread  
38.Выключаем стенд и переносим SD-карту в Машинку.
39.Далее проводим первоначальную настройку для клиентской машины. Для этого нужно произвести настройку ещё одной SD-карты до 26 пункта.
40.Устанавливаем программу удалённого управления компьютером VNC-Viewer.
       sudo apt install realvnc-vnc-viewer -y
41.Снова скачиваем каталог с готовыми конфигурационными файлами, так как там имеются файлы для клиентской части.
       cd
       git clone https://github.com/Lab305/bibika.git
42.Копируем файлы клиентской программы в домашнюю директорию.
       cp bibika/client/client* ./
43.Открываем в Geany файл client.cpp и изменяем команды сборки:
       g++ -Wall -c "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread
       g++ -Wall -o "%e" "%f" -lbcm2835 -lAura -lwiringPi -lm -pthread
44.Подключаемся к настроенной точке доступа на машинке.
  Включаем машинку и ждём до тех пор, пока не появится новая WiFi-сеть с именем Gonka.
  Нажимаем на значок двух стрелочек вверху-слева и нажимаем в появившейся влкладке "Turn On Wi-Fi".
  Снова нажимаем на эту стрелочку и выбираем Wi-Fi-сеть "Gonka". В качестве пароля вводим Gonka1234.
  Подключение должно быть успешным.
45.Подключение к машинке.
  На клиентской машине необходимо запустить VNC-Viewer. Для этого нужно нажать на значок малины вверху-слева,
  в выпадающем меню навести курсор на пункт "Интернет" и выбрать "VNC-Viewer".
  В программе VNC-Viewer в верхней текстовой строке вводим адрес машинки 192.168.4.1
  Заходим под пользователем pi, с паролем raspberry.
46.Запускаем на машинке программу server.cpp через Geany.
  Появится окошко в котором будет написано "Waiting for a Client".
47.Запускаем на клиенте программу client.cpp через Geany.
  После этого, машинка должна сразу же поехать.
