from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from webdriver_manager.chrome import ChromeDriverManager
from selenium import webdriver
import csv
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))
driver.implicitly_wait(10)
data_list=[]
data_list.append(["Year","PLAYER","TEAM","G","AB","R","H","2B","3B","HR","RBI","BB","SO","SB","CS","AVG","OBP","SLG","OPS"
            ,"PA"
            ,"HBP"
            ,"SAC"
            ,"SF"
            ,"GIDP"
            ,"GO"
            ,"XBH"
            ,"TB"
            ,"IBB"
            ,"BABIP"
            ,"ISO"
            ,"AB/HR"
            ,"BB/K"
            ,"BB%"
            ,"SO"])
for year in range(2023,2002,-1):
    driver.get("https://www.mlb.com/stats/"+str(year)+"?playerPool=ALL")
    time.sleep(3)
    print(driver.title)
    if year==2023:
        driver.find_element(By.XPATH,'//*[@id="onetrust-accept-btn-handler"]').click()

##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##2023 
    button_list_list=driver.find_element(By.XPATH,'//*[@id="stats-app-root"]/section/section/div[3]/div[2]/div/div/div[1]')
#//*[@id="stats-app-root"]/section/section/div[3]/div[2]/div/div/div[1]
    n=button_list_list.text
    num_list=n.split("\n")
    num=num_list[-1]
    print(num)
    for i in range(1,2):
        for page in range(1,int(num)+1):
            driver.get("https://www.mlb.com/stats/"+str(year)+"?page="+str(page)+"&playerPool=ALL")
            time.sleep(3)
            tags=driver.find_element(By.CLASS_NAME,"notranslate")
            tags_list=tags.find_elements(By.TAG_NAME,'tr')
        
            name=[]
            team=[]
            g=[]
            ab=[]
            r=[]
            h=[]
            two=[]
            three=[]
            hr=[]
            rbi=[]
            bb=[]
            so=[]
            sb=[]
            cs=[]
            avg=[]
            obp=[]
            slg=[]
            ops=[]
            for element in tags_list:
                element_list=element.text.split("\n")
                player_name=element_list[1]
                data_array=element_list[3].split(" ")
                Team=data_array[0]
                G_player=data_array[1]
                AB_player=data_array[2]
                R_player=data_array[3]
                H_player=data_array[4]
                two_player=data_array[5]
                three_player=data_array[6]
                HR_player=data_array[7]
                RBI_player=data_array[8]
                BB_player=data_array[9]
                SO_player=data_array[10]
                SB_player=data_array[11]
                CS_player=data_array[12]
                AVG_player=data_array[13]
                OBP_player=data_array[14]
                SLG_player=data_array[15]
                OPS_player=data_array[16]
                name.append(player_name)
                team.append(Team)
                g.append(G_player)
                ab.append(AB_player)
                r.append(R_player)
                h.append(H_player)
                two.append(two_player)
                three.append(three_player)
                hr.append(HR_player)
                rbi.append(RBI_player)
                bb.append(BB_player)
                so.append(SO_player)
                sb.append(SB_player)
                cs.append(CS_player)
                avg.append(AVG_player)
                obp.append(OBP_player)
                slg.append(SLG_player)
                ops.append(OPS_player)
            button_click = driver.find_element(By.XPATH, '//*[@id="stats-app-root"]/section/section/div[1]/div[2]/div/div[1]/div/div[2]')
            button_click.click()
            time.sleep(3)
            tags=driver.find_element(By.CLASS_NAME,"notranslate")
            tags_list=tags.find_elements(By.TAG_NAME,'tr')
            pa=[]
            hbp=[]
            sac=[]
            sf=[]
            gidp=[]
            go=[]
            xbh=[]
            tb=[]
            ibb=[]
            babip=[]
            iso=[]
            hh=[]
            k=[]
            bba=[]
            soa=[]
            for element in tags_list:
                element_list=element.text.split("\n")
                data_array=element_list[3].split(" ")
                PA_player=data_array[1]
                HBP_player=data_array[2]
                SAC_player=data_array[3]
                SF_player=data_array[4]
                GIDP_player=data_array[5]
                GO_player=data_array[6]
                XBH_player=data_array[7]
                TB_player=data_array[8]
                IBB_player=data_array[9]
                BABIP_player=data_array[10]
                ISO_player=data_array[11]
                HH_player=data_array[12]
                K_player=data_array[13]
                BBA_player=data_array[14]
                SOA_player=data_array[15]
            
                pa.append(PA_player)
                hbp.append(HBP_player)
                sac.append(SAC_player)
                sf.append(SF_player)
                gidp.append(GIDP_player)
                go.append(GO_player)
                xbh.append(XBH_player)
                tb.append(TB_player)
                ibb.append(IBB_player)
                babip.append(BABIP_player)
                iso.append(ISO_player)
                hh.append(HH_player)
                k.append(K_player)
                bba.append(BBA_player)
                soa.append(SOA_player)
        
            for i in range(0,len(name)):
                data_list.append([str(year),name[i],team[i],g[i],ab[i],r[i],h[i],two[i],three[i],hr[i],rbi[i],bb[i],so[i],sb[i],cs[i],avg[i],obp[i]
                ,slg[i],ops[i],pa[i],hbp[i],sac[i],sf[i],gidp[i],go[i],xbh[i],tb[i],ibb[i],babip[i],iso[i],hh[i],k[i],bba[i],soa[i]
                                ])

driver.quit()
csvfile = "player_hitting.csv"
with open(csvfile, 'w+', newline='', encoding="utf-8") as fp:
    writer = csv.writer(fp)
    for i in data_list:
        #print(i+"\n")
        writer.writerow(i)