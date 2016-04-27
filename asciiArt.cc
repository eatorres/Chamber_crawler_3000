#include "asciiArt.h"

using namespace std;

void welcomeMsg(){
	cout << "\033[1;32m\n";
	cout << "__          __  _                            _        " << endl;
	cout << "\\ \\        / / | |                          | |       "<< endl;
	cout << " \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___  " << endl;
	cout << "  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\ " << endl;
	cout << "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |" << endl;
	cout << "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ " << endl;
	cout << endl;
	cout << endl;
	cout << "      _                     _               " << endl;
	cout << "     | |                   | |              " << endl;
	cout << "  ___| |__   __ _ _ __ ___ | |__   ___ _ __ " << endl;
	cout << " / __| '_ \\ / _` | '_ ` _ \\| '_ \\ / _ \\ '__|" << endl;
	cout << "| (__| | | | (_| | | | | | | |_) |  __/ |   " << endl;
	cout << " \\___|_| |_|\\__,_|_| |_| |_|_.__/ \\___|_|   " << endl;
	cout << endl;
	cout << endl;
	cout << "                         _             ____   ___   ___   ___  " << endl;
	cout << "                        | |           |___ \\ / _ \\ / _ \\ / _ \\ " << endl;
	cout << "  ___ _ __ __ ___      _| | ___ _ __    __) | | | | | | | | | |" << endl;
	cout << " / __| '__/ _` \\ \\ /\\ / / |/ _ \\ '__|  |__ <| | | | | | | | | |" << endl;
	cout << "| (__| | | (_| |\\ V  V /| |  __/ |     ___) | |_| | |_| | |_| |" << endl;
	cout << " \\___|_|  \\__,_| \\_/\\_/ |_|\\___|_|    |____/ \\___/ \\___/ \\___/ " << endl;
	cout << "\033[47m";
	cout << "\033[0;37m\033[40m";
	cout << endl;
	cout << endl;
}

string welcome(){
	cout << "Please enter a race, h(human), d(dwarf), e(elf) or o(orc): " << endl;
	string race;
	cin >> race;
	return race;
}

void win(){
	cout << "........ .. .       ..            . .     . .    ...  . .  ............" << endl;
	cout << "........                   ~==MMMMM~= .   . .    . .  . .  ............" << endl;
	cout << ".  ....           .MMMMMMM. ...    ..MMM.        .         ............" << endl;
	cout << ".  .  .     ..MMM.                      MMM                ............" << endl;
	cout << ".  .  .  MMMI .                            MN.        .    ............" << endl;
	cout << ".. .    M~.                                  M8       .    ............" << endl;
	cout << ".  .  .M.                                     .M.          ............" << endl;
	cout << ".  . :M.                                     ZMMM+ MM$     ............" << endl;
	cout << ".  ..M                                     MM.    .MMMMN.  ............" << endl;
	cout << ".   MD.                                  .M       MMMMMM.  ............" << endl;
	cout << ".  .M..                                  M,       MMMMMMM  ............" << endl;
	cout << ".  M: .                             .    M,        .MMMMM  ............" << endl;
	cout << ".  M  .                                  MM           .M.  ............" << endl;
	cout << ".  M  ..         .  MMMMMM,.              M           MM   ............" << endl;
	cout << ". MM  .        NMMMMMMMMMM.MM             ,MM.   . .MM     ............" << endl;
	cout << ". M   .       MM  MMMMMMMM  M               MMMMMMMMM      ............" << endl;
	cout << ". M   .      M.    MMMMM8   M               .    . MM      ............" << endl;
	cout << "..M ....     M..     .     .M. .  . .     . ..   . M. . .  ............" << endl;
	cout << ". MM  .     .M             8M.        MMM.M       ZM       ............" << endl;
	cout << ".  M  .      .M           MM   MMMMMMM.M  M      MM        ............" << endl;
	cout << ".  M  ..       M       DMM   MM..M  M.   M.     MM.        ............" << endl;
	cout << ".  M: ..       . MMMMM. .    M.      . .M      MM.         ............" << endl;
	cout << ".  .M..                       MM?M  +?MD  .   MM .         ............" << endl;
	cout << ".  . M~                        .            MM.  .         ............" << endl;
	cout << ".  . .8M,                                MMO.              ............" << endl;
	cout << ".  .  . 8M.                          .MMM .                ............" << endl;
	cout << ".  .  .   .MM                    MMMM M   .                ............" << endl;
	cout << ".  .  ..   M                MMMM .  .M                  .  ............" << endl;
	cout << ".  .  .  ,M.                      .  M.   .      .    . .  ............" << endl;
	cout << "....... MM          .   .  .      . .M. ... .   .. .... .. ............" << endl;
	cout << ".  .  .M      Z     ZMMMZZ           M.  .MMMMMMMNM        ............" << endl;
	cout << "......M.      M.   M     .+M   .  . .MMMMM. .  .M. MM . .  ............" << endl;
	cout << ".  . :M        ....        8D         M     M   M   M      ............" << endl;
	cout << ".....:M.       .            M     . . M   ..MM ,M. .M.. .  ............" << endl;
	cout << ".  ..MM                     M         M   .          M     ............" << endl;
	cout << ".   M. M,                   M       . M.            M      ............" << endl;
	cout << ".  M: . ZMMNMMMMMM         .M     .   MMMMMMM.    $M.      ............" << endl;
	cout << ". .M  .          ,MMMMMMMMMM.          M     ,MMMM         ............" << endl;
	cout << ". M   .                                M                   ............" << endl;
	cout << endl;
	cout << endl;
	cout << "					YOU WIN 											" << endl;

}


void restart(){
	cout << "\033[1;34m\n";
	cout << " _____           _             _   " << endl;
	cout << "|  __ \\         | |           | |  " << endl;
	cout << "| |__) |___  ___| |_ __ _ _ __| |_ " << endl;
	cout << "|  _  // _ \\/ __| __/ _` | '__| __|" << endl;
	cout << "| | \\ \\  __/\\__ \\ || (_| | |  | |_ " << endl;
	cout << "|_|  \\_\\___||___/\\__\\__,_|_|   \\__|" << endl;
	cout << "\033[0;37m\033[40m";
	cout << endl;
	cout << endl;
}

void gameOver(){
	cout << "\033[1;31m\n";
	cout << "  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███  " << endl;
	cout << " ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒" << endl;
	cout << "▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒" << endl;
	cout << "░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄  " << endl;
	cout << "░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒" << endl;
	cout << " ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░" << endl;
	cout << "  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░" << endl;
	cout << "░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░ " << endl;
	cout << "      ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░     " << endl;
	cout << "                                                     ░                   " << endl;
	cout << "\033[0;37m\033[40m\n";

}