unzip big.zip # this works quite fast and the file resulted file is about 400MB
unzip -p big.zip | tr -d ' \n' # This works slow about 2 hours, but doesn't use an additional HDD memory, so it's applicable. 

# but with grep it's faster, because it will print output as soon as it will be found
unzip -p big.zip | grep -o '\S'