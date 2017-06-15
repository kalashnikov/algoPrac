import os
import requests
from bs4 import BeautifulSoup
from slacker import Slacker

msg_list = []

for book_id in ['713201', '713068', '713115', '713056']:
    url = 'http://webpac.tphcc.gov.tw/toread/opac/bibliographic_view?classification_type=all&id={}&language=all&level=all&limit=20&material_type=all&mps=20&offset=local%3A0&source=local&view=CONTENT&wi=false'.format(book_id)
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')

    title = soup.find('li', class_='reslt_item_head').text.strip()

    is_availabe = False
    
    for s in soup.find_all('tr', class_='gridTr'):
        l = [ss for ss in s.strings]
        if "在架" in l[7] and l[8].strip() == "0":
            if not is_availabe: 
                msg = '{} | {}'.format(title, url)
                msg_list.append(msg)
                is_availabe = True
            
            msg = '\t{} {} {}'.format(l[2].strip(), l[7].strip(), l[8].strip())
            msg_list.append(msg)

if len(msg_list)!=0:
    msg = "\n".join(msg_list)
    slack = Slacker(os.environ['SLACKER_TOKEN'])
    slack.chat.post_message('#bookmonitor', msg)
    #print(cmd)
