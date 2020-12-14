<!--
Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
Distributed under the terms of the GNU General Public License, version 3
-->

# Configuring a computer network

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![License: CC BY-NC-ND 4.0](https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-nd/4.0/)

![test](https://github.com/dmfrodrigues/feup-rcom-l2/workflows/test/badge.svg)

- **Project name:** Configuring a computer network
- **Short description:** Configuring a computer network with two virtual subnetworks, a router computer and a router to access the Internet
- **Environment:** Unix machines, Cisco Catalyst 3560 v2 series switch, MikroTik RB3011 UiAS-RM routerboard
- **Tools:** FTP, C, GTKTerm (configure switch/router)
- **Institution:** [FEUP](https://sigarra.up.pt/feup/en/web_page.Inicial)
- **Course:** [RCOM](https://sigarra.up.pt/feup/en/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=459483) (Computer Networks)
<!-- - **Project grade:** ??.?/20.0 -->
- **Group members:**
    - [Breno Accioly de Barros Pimentel](https://github.com/BrenoAccioly) (<up201800170@fe.up.pt>)
    - [Diogo Miguel Ferreira Rodrigues](https://github.com/dmfrodrigues) (<dmfrodrigues2000@gmail.com> / <diogo.rodrigues@fe.up.pt>)

## Computers

FEUP, room I321, bench 3

## The project

### Part 1 - download application

A simple FTP client.

#### Compile

To compile, run `make -C download`. Here are some other interesting `make` options:

```sh
make -C download test           # Run tests that do not require FEUP VPN
make -C download test_all       # Run all tests
make -C download clean          # Cleanup directory
```

#### Use

```txt
download ftp://[<user>:<password>@]<host>/<url-path>

Download a file over FTP using a regular FTP URL.
```

See [`download/makefile`](download/makefile) for some examples.

# License

© 2020 Diogo Rodrigues, Breno Pimentel

All files are licensed under [GNU General Public License v3](LICENSE) by **© 2020 Diogo Rodrigues, Breno Pimentel**, to the exception of:
<!-- - all files inside directory `doc/guidelines`, which were authored by the lecturers; -->
- all files inside directory `doc/report` and all artifacts deriving from them, which are licensed under the [Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International](doc/report/LICENSE) public license. -->

The files not authored by us are presented as a fundamental complement to the presented solutions, and are made available under *fair use for education*.

