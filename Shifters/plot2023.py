import pandas as pd

#
#     2023-03-15.List_participant_Completed_CMS\ _Shifter\&Slimos__courses_From_April_2020_until_15_Marc.xls 
#     =
#     2023-03-15.SLandTS.xls
#


df = pd.read_excel(
                   "2023-03-15.SLandTS.xls", 
                   sheet_name='Participant',
                   skiprows=[0,1]
                   )

df.keys()

print (" df = ", df)

df_TS = df.loc[
               df['Names of the course'].str.contains('Technical Shifter')
               &
               df['training status'].str.contains('Completed')
               ] 

df_TS['Training date']


df_TS_count = df_TS[['Training date', 'Dep/Group/Section', 'Participant Name']].groupby('Training date').count()

df_TS_count['date'] = df_TS_count.index

df_TS_count['date'] = pd.to_datetime(df_TS_count['date'])

df_TS_count['count'] = df_TS_count['Dep/Group/Section']

df_TS_count_sort  = df_TS_count.sort_values(by='date')


df_TS_count_sort['cumulative'] = df_TS_count_sort['count'].cumsum()






import matplotlib.pyplot as plt

plt.plot(df_TS_count_sort['date'], df_TS_count_sort['cumulative'], '*')
plt.xticks(rotation='vertical')

#plt.show()




print ("TS done, now SL!")


df_SL = df.loc[
               df['Names of the course'].str.contains('Shift Leader')
               &
               df['training status'].str.contains('Completed')
               ] 

df_SL['Training date']

print (" df_SL = ", df_SL)

df_SL_count = df_SL[['Training date', 'Dep/Group/Section', 'Participant Name']].groupby('Training date').count()

df_SL_count['date'] = df_SL_count.index

df_SL_count['date'] = pd.to_datetime(df_SL_count['date'])

df_SL_count['count'] = df_SL_count['Dep/Group/Section']

df_SL_count_sort  = df_SL_count.sort_values(by='date')


df_SL_count_sort['cumulative'] = df_SL_count_sort['count'].cumsum()


print (" df_SL_count = ", df_SL_count)


print ("plot all and done")


import matplotlib.pyplot as plt


fig = plt.figure()
fig.patch.set_facecolor('white')

plt.clf()

plt.plot(df_TS_count_sort['date'], df_TS_count_sort['cumulative'], '*', label="TS")
plt.plot(df_SL_count_sort['date'], df_SL_count_sort['cumulative'], '+', label="SL")

plt.xlabel('date')
plt.ylabel('trained people', fontsize='large')

plt.legend(loc='upper left')

plt.xticks(rotation='vertical')


plt.show()



