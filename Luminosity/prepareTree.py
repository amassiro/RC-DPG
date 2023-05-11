import io
import subprocess

import numpy
import pandas

unit = '/ub'

def query(fill: int) -> pandas.DataFrame:
    cmd = ['.local/bin/brilcalc', 'lumi', '-f', str(fill), '-b', 'stable beams', '--output-style', 'csv', '--tssec', '--xing', '-u', unit]
    data = subprocess.run(cmd, capture_output=True, text=True)
    names = [col.strip() for col in data.stdout.splitlines()[1].lstrip('#').split(',')]
    data = pandas.read_csv(io.StringIO(data.stdout), names=names, comment='#')
    data[['run', 'fill']] = data['run:fill'].str.split(':', expand=True)
    data[['ls', 'cms_ls']] = data['ls'].str.split(':', expand=True)
    data = data.apply(pandas.to_numeric, errors='ignore')
    data['datetime'] = pandas.to_datetime(data['time'], unit='s', utc=True)
    return data

def parse_bx_data(bx_data: pandas.Series):
    bx_data = bx_data.str[1:-1].apply(numpy.fromstring, dtype=float, sep=' ')
    bcid = bx_data.str[0::3].rename('bcid')
    delivered = bx_data.str[1::3].rename(f'delivered ({unit})')
    recorded = bx_data.str[2::3].rename(f'recorded ({unit})')
    if (delivered.apply(numpy.size) == 3564).all():
        return pandas.DataFrame(delivered.to_list())

def main(fill: int = 8736):
    fill_data = query(fill=fill)
    bx_data = parse_bx_data(bx_data = fill_data[f'[bxidx bxdelivered({unit}) bxrecorded({unit})]'])
    fill_data = pandas.concat([fill_data[['fill', 'run', 'ls', 'datetime', 'time', 'avgpu']], bx_data], axis=1)
    fill_data.to_csv(f'fill_{fill}.csv', index=False)

main(fill=8736)
fill_8736 = pandas.read_csv('fill_8736.csv')
print(fill_8736[(fill_8736.run == 367232) & (fill_8736.ls <= 10)][['run', 'ls', 'datetime', 'avgpu'] + [str(bx) for bx in range(137,149)]])

