#
# HEX2COM
# IntelHexファイルを MSX-DOS / CP/M の COMファイルに変換する
#
# This code is provided under a CC0 Public Domain License.
# http://creativecommons.org/publicdomain/zero/1.0/
# 
# 2024年12月03日 佐藤恭一 kyoutan.jpn.org
#
# pyinstaller --onefile hex2com.py
# でwindowsのEXE形式にすることもできる

import sys,os
from intelhex import IntelHex

def usage():
    print('HEX2COM        kyoutan.jpn.org')
    print('Convert IntelHex format files to MSX-DOS / CP/M COM format.')
    print('')
    print('HEX2COM <filename> [-d] [-h]')
    print('    -d Hexadecimal dump view')
    print('    -h Show Help')

args=sys.argv
filename=''
option=''

# コマンドライン引数が無ければ使い方を表示して終了
if 1==len(args):
    usage()
    sys.exit()

# コマンドライン引数をしらべる
for i, arg in enumerate(args):
    if i==0:
        continue    # ゼロ番目の引数（コマンド名）はなにもしない
    
    #print(f'引数 {i}: {arg}')
    if not arg.startswith('-'):
        filename=arg                    # 一文字目が '-'ではないときはファイル名として扱う
    elif arg.upper().startswith('-H'):
        #print('-H')
        usage()
        sys.exit()
    elif arg.upper().startswith('-D'):
        #print('-D')
        option='DUMP'

# コマンドライン引数を調べたけどファイルネームが無いので終了
if ''==filename:
    #print('ファイルネームがない')
    usage()
    sys.exit()

print('input  filename:',filename)
# IntelHexファイルを読み込む
hexfile=IntelHex(filename)

# -D オプションならダンプ表示だけを行って終了
if 'DUMP'==option:
    hexfile.dump()
    sys.exit()

if 0x100!=hexfile.minaddr():
    # アドレスが 0x100から始まっていない場合は処理中止
    print('The start address was not 0x100, so no processing was performed.')
    sys.extt()

# バイナリファイルを書き出し
outputfilename=os.path.splitext(filename)[0]+'.com'
print('output filename:',outputfilename)
hexfile.tobinfile(outputfilename)
sys.exit()
