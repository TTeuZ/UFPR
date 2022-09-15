import os
import linecache
import pandas as pd

groups = {
    'TIME': [13, 36, 59],
    'MEM': [28, 51, 74],
    'CACHE': [32, 58, 84],
    'FLOPS_DP': [28, 50, 72]
}
matrix_sizes = [32, 33, 64, 65, 128, 129, 256, 257, 512, 1000, 2000, 4000, 6000, 10000]
versions = ['v1','v2']

df_time = pd.DataFrame(columns=['matrix_size', 'op1-v1', 'op2-v1', 'op1-v2', 'op2-v2'])
df_mem = pd.DataFrame(columns=['matrix_size', 'op1-v1', 'op2-v1', 'op1-v2', 'op2-v2'])
df_cache = pd.DataFrame(columns=['matrix_size', 'op1-v1', 'op2-v1', 'op1-v2', 'op2-v2'])
df_flops = pd.DataFrame(columns=['matrix_size', 'op1-v1', 'op2-v1', 'op1-v2', 'op2-v2'])

for group in groups:
    for matrix_size in matrix_sizes:
        # create lists of features
        time_list = [matrix_size]
        mem_list = [matrix_size]
        cache_list = [matrix_size]
        flops_list = [matrix_size]

        for version in versions:      
            op1_list = []
            op2_list = []
            for line in groups[group]:
                # get the right file for time attribute
                if group == 'TIME':
                    file = './logs/' + version + '-' + str(matrix_size) + '-' + 'MEM' + '.log'
                else:
                    file = './logs/' + version + '-' + str(matrix_size) + '-' + group + '.log'
                data = linecache.getline(file, line)
                
                try:
                    file_data = data.split(',')[1]
                    if line == groups[group][-1]:
                        op2_list.append(float(file_data))
                    else:
                        op1_list.append(float(file_data))
                except IndexError:
                    print('!-- Data not found for ', file, '!!!')
                
                if group == 'TIME':
                    # last line
                    if line == groups[group][-1]:
                        time_list.append(sum(op1_list))
                        time_list.append(op2_list[0])
                        
                        if (len(time_list) == 5):
                            df_time = pd.concat([pd.DataFrame([time_list], columns=df_time.columns), df_time], ignore_index=True)
                        
                elif group == 'MEM':
                    # last line
                    if line == groups[group][-1]:
                        mem_list.append(sum(op1_list))
                        mem_list.append(op2_list[0])
                        
                        if (len(mem_list) == 5):
                            df_mem = pd.concat([pd.DataFrame([mem_list], columns=df_mem.columns), df_mem], ignore_index=True)
                              
                elif group == 'CACHE':
                    # last line
                    if line == groups[group][-1]:
                        cache_list.append(sum(op1_list))
                        cache_list.append(op2_list[0])
                        
                        if (len(cache_list) == 5):
                            df_cache = pd.concat([pd.DataFrame([cache_list], columns=df_cache.columns), df_cache], ignore_index=True)
                                 
                elif group == 'FLOPS_DP':
                    # last line
                    if line == groups[group][-1]:
                        flops_list.append(sum(op1_list))
                        flops_list.append(op2_list[0])
                        
                        if (len(flops_list) == 5):
                            df_flops = pd.concat([pd.DataFrame([flops_list], columns=df_flops.columns), df_flops], ignore_index=True)

print('creating time.csv')
df_time.to_csv('./csvs/time.csv', index=False)
print('creating mem.csv')
df_mem.to_csv('./csvs/mem.csv', index=False)
print('creating cache.csv')
df_cache.to_csv('./csvs/cache.csv', index=False)
print('creating flops.csv')
df_flops.to_csv('./csvs/flops.csv', index=False)