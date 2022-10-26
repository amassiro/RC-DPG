import pandas as pd

df = pd.read_excel(
                   "2022-10-21.report_participant_CMS_Shifter&Slimos_completed-since_2019.xls", 
                   sheet_name='CMS Shifter',
                   skiprows=[0,1,3,4,5,6,7,8]
                   )

df.keys()

df_TS = df.loc[
               df['Name of course'].str.contains('Technical Shifter')
               &
               df['status'].str.contains('Completed')
               ] 

df_TS['Date of training']


df_TS_count = df_TS[['Date of training', 'mail contact', 'Name of participant']].groupby('Date of training').count()

df_TS_count['date'] = df_TS_count.index

df_TS_count['date'] = pd.to_datetime(df_TS_count['date'])

df_TS_count['count'] = df_TS_count['mail contact']

df_TS_count_sort  = df_TS_count.sort_values(by='date')


df_TS_count_sort['cumulative'] = df_TS_count_sort['count'].cumsum()






import matplotlib.pyplot as plt

plt.plot(df_TS_count_sort['date'], df_TS_count_sort['cumulative'], '*')
plt.xticks(rotation='vertical')

plt.show()







df_SL = df.loc[
               df['Name of course'].str.contains('Shift Leader')
               &
               df['status'].str.contains('Completed')
               ] 

df_SL['Date of training']


df_SL_count = df_SL[['Date of training', 'mail contact', 'Name of participant']].groupby('Date of training').count()

df_SL_count['date'] = df_SL_count.index

df_SL_count['date'] = pd.to_datetime(df_SL_count['date'])

df_SL_count['count'] = df_SL_count['mail contact']

df_SL_count_sort  = df_SL_count.sort_values(by='date')


df_SL_count_sort['cumulative'] = df_SL_count_sort['count'].cumsum()






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



