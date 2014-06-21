# -*- coding: cp936 -*-
from BeautifulSoup import BeautifulSoup as BS
import urllib2
import sys

url = sys.argv[1]
request = urllib2.urlopen(url)
charset = request.info().getparam('charset') #获得当前网页编码
html_doc = request.read().decode(charset).encode('utf-8')

soup = BS(''.join(html_doc))
#print soup.body.findAll('h1')[0].string

cs = soup.body.findAll('cc')
for c in cs[0].div.contents:
    if "br " in c: continue
    print c 
    print '\n'

#for content in contents:
#    print content.div.contents[0]
#    print '\n'
