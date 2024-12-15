# backsh: Backup shell
The backsh is a program
intended to be specified as a shell in a remote backup host computer,
allowing potentially untrusted clients to backup data to the
specified directory,
without providing them remote access to a command shell or the ability to
delete existing backup files.
Consult [the provided manual page](https://dspinellis.github.io/manview/?src=https://raw.githubusercontent.com/dspinellis/backsh/refs/heads/main/backsh.1) for more information.

## Installation
make install

## Use example
```
[backup-client]$ tar czf - . |
> ssh backsh@backup-host.example.com backup-files backup.tar.gz

[backup-host]$ ls backup-files
20231214Z123456-backup.tar.gz
```
