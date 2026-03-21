#.................................................................................................................
#  author : Mulatu yirga                                                                                       .
#  date :   12/07/2023 E.C    
#  sample of Python Code for BSM classification                                                                                    .     
#.................................................................................................................

#...to import neccessary librabries.......
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
sns.set()
from sklearn.cluster import KMeans

#read Node-3.csv file
BSM_data = pd.read_csv("/home/mulatu/Mobility1/Node-3.csv", skipinitialspace=True)

#filter data recieved at 100, 200,300,400,...1000ms specified filter data recieved at 100ms only
BSM_data = BSM_data[BSM_data['Brdcast_Time(ms)'] == 100]
print("BSM-DATA Received by Node-3 at 100ms from its Neighboring Nodes are:\n", BSM_data)

 # Assign the BSM as Data-Frame data for further experiments
 #Note We used a fixed cluster Centroid Values,RSS from the experiment value[14]

def RankingScheme(): 
    
    #load bsm data to dataframe
    df = pd.DataFrame(BSM_data)
    df=df.round(3)
    
    #Create a list of all rss in the 'df'
    list_of_rss = []
    for i in range (-90, -30):
        list_of_rss.append(i)

    #.................BSM Classification............................................... 
    # We used rss value from experiment on 'accuracy of BSM classification based on K-Means Clustering' by in [14]
    #.............................................................................................................
    
    #.....the 1st safety area.....
    for rss in list_of_rss:
        condition = df['rss'] >= -62
        SA1 = df[condition]

    #If the filtered data has some records
    print("BSM is found in distance between 0-50m")
    if len (SA1) > 0:
        #Now Rank BSMs within SA1 Using distance values 
        SA1["rankD_1"] = SA1['distance'].rank()
        SA1.sort_values('distance', inplace = True)
        
        #Now Rank BSMs within SA1 Using arrival values 
        SA1["rankAT_1"] = SA1['arrivalTime'].rank()
        SA1.sort_values('arrivalTime', inplace = False)
        
        
        #After ranking
        print(".SA1 After Rank.")
        print(SA1)
    
    #.....the 2nd safety area.....
    for rss in list_of_rss:
        condition = df['rss'] <= -62 
        SA2 = df[condition]
    print("\nBSM is found in distance between 50-100m")
    if len (SA2) > 0:
        SA2["Rank_SA2"] = SA2['distance'].rank()
        SA2.sort_values('distance', inplace = True)
        
		#After Ranking
        print(".SA2 After Rank.")
        print(SA2)

    #.....the 3rd safety area.....  
    for rss in list_of_rss:
        condition = df['rss'] <= -78
        SA3 = df[condition]
    print("\nBSM is found in distance between 100-150m")
    if len (SA3) > 0:
        SA3["Rank_SA3"] = SA3['distance'].rank()
        SA3.sort_values('distance', inplace = True)
                
        print(".SA3 After Rank.")
        print(SA3)

    #.....the 4th safety area.....   
    for rss in list_of_rss:
        condition = df['rss'] <= -84
        SA4 = df[condition]
    print("\nBSM is found in distance between 150-200m")
    if len (SA4) > 0:
        SA4["Rank_SA4"] = SA4['distance'].rank()
        SA4.sort_values('distance', inplace = True)

        print(".SA4 After Rank.")
        print(SA4)

    #.....the 5th safety area.....   
    for rss in list_of_rss:
        condition = df['rss'] <= -90
        SA5 = df[condition]
    print("\nBSM is found in distance between above 200m")
    if len (SA5) > 0:
        SA5["Rank_SA5"] = SA5['distance'].rank()
        SA5.sort_values('distance', inplace = True)

        print(".SA5 After Rank.")
        print(SA5)

# RankingScheme function
  RankingScheme()
 #============================================================
 # sample of Python Code for Trusted based approach
 #============================================================
for i in sorted_nodesInfo:
 if i[0]!=0:
  if i[0]!=s_id:
    s_id = i[0]
        count=0
    else:
        if count>= th :
            if s_id in RSU[’Sdr_Id’].values:
            count=0
            continue
    else:
        count+=1
       jumped_nd_info.append([i[0], i[1]])
 else:
jumped_nd_info.append([i[0], i[1]])
#=============================================================


