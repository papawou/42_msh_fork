## This commands need to work before merging to develop :

- [ ] display /etc/passwd content
```
cat /etc/passwd
```

- [ ] display /etc/passwd root line
```
cat /etc/passwd | grep root
```

- [ ] add /etc/passwd root line to tmp file
```
cat /etc/passwd | grep root > /tmp/test-out
```

- [ ] Append /etc/passwd root line to tmp file
```
cat /etc/passwd | grep root >> /tmp/test-out
```

- [ ] Get /etc/passwd as input file syntax one
```
< /etc/passwd cat -n
```

- [ ] Get /etc/passwd as input file syntax two
```
cat -n < /etc/passwd 
```

- [ ] display home path
```
echo "$HOME"
```

- [ ] display home path / editor
```
echo "$HOME/$EDITOR"
```

- [ ] Get from stdin syntax one
```
<< EOF cat -n
```

- [ ] Get from stdin syntax two
```
cat -n << EOF
```

- [ ] Change directory
```
cd /tmp
```

- [ ] Should go to home
```
cd
```
