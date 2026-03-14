# Music App

This is a command-line music management application in C. It lets users manage a music library, organize songs into albums, create playlists, and simulate playback in a loop.

Users can:
- View and manage songs and albums
- Build playlists and play, skip, or remove songs
- Save albums and command logs across sessions

The program uses modular C code with **linked lists** for storing songs, albums, and playlists. A **Makefile** is included for easy building and running.

## Prerequisites

You need a **C compiler (`gcc`)** and **`make`** installed.

**Linux (Debian/Ubuntu):**

```bash
sudo apt update
sudo apt install build-essential
```

**macOS:**

```bash
xcode-select --install
```

**Windows:**
Install **MinGW-w64** or **Cygwin** and ensure `gcc` and `make` are available in your system PATH.

---

## Build and Run

1. Open a terminal and navigate to the project folder:

```bash
cd /path/to/project
```

2. Compile the program using the Makefile:

```bash
make
```

This will build the executable **`music_app`**.

3. Run the program:

```bash
./music_app
```

On Windows, run:

```bash
music_app.exe
```

---

## Clean Build Files

To remove compiled object files and the executable:

```bash
make clean
```

---

## Notes

* Run `make` from the **same directory as the `Makefile`**.
* No additional configuration is required once prerequisites are installed.
