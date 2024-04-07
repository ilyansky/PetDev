all: push

ignore:
	echo ".DS_Store" > .gitignore

push:
	git add -A
	git commit -m "ilyansky"
	git push