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
