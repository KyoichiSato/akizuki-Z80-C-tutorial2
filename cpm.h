
/*
CP/M / MSX-DOS ファンクションコール関数
アセンブラ関数本体は "cpm.xas"

This code is provided under a CC0 Public Domain License.
http://creativecommons.org/publicdomain/zero/1.0/

2024年12月11日 作成 佐藤恭一 kyoutan.jpn.org
*/

#ifndef _CPM_H
#define _CPM_H

/* SPレジスタの値を返す */
unsigned short _GETSPREG(void);

/* このアプリケーションが設定するスタックポインタの初期値
（このプログラムがロードされる最終アドレスポインタ）を取得する */
unsigned short *_GETENDADDR(void);

/* TPAの最終アドレスポインタを取得する */
#define _GETTPAADDR() (*((unsigned short *)(0x0006)) - 1)

/* CP/M 0x00 ウォームリセット */
void CPMRESET(void);

/* CP/M 0x01 コンソール入力 入力があるまで待つ
    戻り値 入力文字 */
char CPMGETC(void);

/* CP/M 0x02 コンソール出力
    c 出力文字 */
void CPMPUTC(char c);

/* CP/M 0x03 補助入力
    戻り値 入力文字 */
char CPMAUXGETC(void);

/* CP/M 0x04 補助出力
    c 出力文字 */
void CPMAUXPUTC(char c);

/* CP/M 0x05 プリンタ出力
    c 出力文字 */
void CPMPRNPUTC(char c);

/* CP/M 0x06 直接コンソール入出力
    c 0xFF 入力 / それ以外 出力文字
    戻り値 入力の場合文字コード、0x00なら入力なし 出力の場合戻り値無し
    入力のエコーバック、コントロールキャラクタの処理は行わない。 */
char CPMCONIO(char c);

/* CP/M 0x07 直接コンソール入力 ※MSX-DOSのみ
    戻り値 入力文字 入力のエコーバック、コントロールキャラクタの処理は行わない。 */
char CPMCONPUTC(void);

/* CP/M 0x08 エコーなしコンソール入力 ※MSX-DOSのみ
    C 出力文字 エコーバックは行わない。コントロールキャラクタは処理する。 */
void CPMRAWGETC(char c);

/* CP/M 0x09 文字列出力
    文字列の終端は '$' C言語と異なるので注意。
    Ctrl-S や Ctrl-C の入力を受け付ける。 */
void CPMPUTS(char *str);

/* CP/M 0x0A 文字列入力
    count 最大入力文字数
    str  行バッファ（最大入力文字数 + 2byte）
    | 最大入力文字数(1byte) | 実際の入力文字数(1byte) | 入力された文字列… |
    戻り値 入力された文字数 */
unsigned char CPMGETS(char *str, unsigned char count);

/* CP/M 0x0B コンソール入力状態のチェック
    戻り値  0x00:入力バッファは空 0xFF:バッファにデータあり */
unsigned char CPMKBDHIT(void);

/* CP/M 0x0C バージョン番号の獲得
    戻り値 バージョン番号（多くは 0x0022） */
unsigned short CPMVER(void);

/* CP/M 0x0D ディスクリセット */
void CPMDSKRESET(void);

/* CP/M 0x0E デフォルトドライブの設定
    drive 0:A 1:B ... */
void CPMSETDRIVE(unsigned char drive);

/* CP/M 0x0F ファイルのオープン
    戻り値 0x00:成功 0xFF:失敗 */
unsigned char CPMOPEN(void *FCB);

/* CP/M 0x10 ファイルのクローズ
    戻り値 0x00:成功 0xFF:失敗 */
unsigned char CPMCLOSE(void *FCB);

/* CP/M 0x11 ファイルの検索（最初の一致）
    戻り値 0x00:ファイルが見つかった 0xFF:見つからなかった */
unsigned char CPMFIND(void *FCB);

/* CP/M 0x12 ファイルの検索（後続の一致）
    戻り値 0x00:ファイルが見つかった 0xFF:見つからなかった
    見つかった場合DTAにドライブ番号を、それに続く32バイトに
    そのファイルのディレクトリエントリをセットする。 */
unsigned char CPMFINDNEXT(void);

/* CP/M 0x13 ファイルの削除
    戻り値 0x00:成功 0xFF:失敗 */
unsigned char CPMDEL(void *FCB);

/* CP/M 0x14 シーケンシャルリード
    戻り値 0x00:成功 0x01:失敗 */
unsigned char CPMSEQREAD(void *FCB);

/* CP/M 0x15 シーケンシャルライト
    戻り値 0x00:成功 0x01:失敗 */
unsigned char CPMSEQWRITE(void *FCB);

/* CP/M 0x16 ファイルの作成
    戻り値 0x00:成功 0xFF:失敗 */
unsigned char CPMCREATE(void *FCB);

/* CP/M 0x17 ファイル名の変更
    FCB+0  旧ファイル名
    FCB+16 新ファイル名
    戻り値 0x00:成功 0xFF:失敗 */
unsigned char CPMREN(void *FCB);

/* CP/M 0x18 ログインベクトルの獲得（つながっているドライブを調べる）
    戻り値 オンラインベクトル情報
    1:online 0:offline
    bit 0 A:
    bit 1 B:
    bit 2 C:
    bit 3 D:
    bit 4 E:
    bit 5 F:
    bit 6 G:
    bit 7 H:
    bit 8-15 '0' */
unsigned short CPMLOGINVEC(void);

/* CP/M 0x19 デフォルトドライブ番号の獲得
    戻り値 デフォルトドライブ番号 0:A 1:B ... */
unsigned char CPMGETDRIVE(void);

/* CP/M 0x1A 転送先アドレス (DTA) の設定
    DTA初期値は 0x0080 */
void CPMSETDTA(void *DTA);

/* CP/M 0x1B ディスク情報の獲得 ※MSX-DOSのみ */
void CPMDISKINFO(unsigned char drive, void *result);

/* CP/M 0x21 ランダムな読み出し（レコード番号の自動インクリメントは行わない）
    FCBのランダムレコード 読み出すレコード番号
    レコードサイズ 128byte固定
    戻り値 0x00:成功 0x01:失敗
    DTA 読み出したデータ 128byte */
unsigned char CPMRNDREAD(void *FCB);

/* CP/M 0x22 ランダムな書き込み（レコード番号の自動インクリメントは行わない）
    FCBのランダムレコード 書き込むレコード番号
    レコードサイズ 128byte固定
    戻り値 0x00:成功 0x01:失敗 */
unsigned char CPMRNDWRITE(void *FCB);

/* CP/M 0x23 ファイルサイズの獲得
    戻り値 0x00:成功 0xFF:失敗
    成功時 FCBのランダムレコードフィールドに
    ファイルサイズを 1/128にした値をセット (128倍にするとファイルサイズ)
    ランダムレコードフィールドに最終レコードの次がセットされる */
unsigned char CPMFILESIZE(void *FCB);

/* CP/M 0x24 ランダムレコードフィールドの設定
    FCBのカレントブロック 目的のブロック
    FCBのカレントレコード 目的のレコード
    をセットして実行すると
    FCBのランダムレコードフィールドに
    カレントブロックとカレントレコードから計算した値をセットする */
void CPMCURRENTFIELD(char *FCB);

/* CP/M 0x26 ランダムブロック書き込み ※MSX-DOSのみ
    RECORD 書き込むレコード数
    FCBのレコードサイズ レコードサイズ
    FCBのランダムレコード 書き込みを開始するレコード
    戻り値 0x00:成功 0x01:失敗 */
unsigned char CPMBLOCKWRITE(void *FCB, unsigned short RECORD);

/* CP/M 0x27 ランダムブロック読み出し ※MSX-DOSのみ
    *RECORD 読み出すレコード数（結果を返すのでポインタ渡し）
    FCBのレコードサイズ レコードサイズ
    FCBのランダムレコード 読み出しを開始するレコード
    戻り値 0x00:成功 0x01:失敗
    *RECORD 実際に読み出したレコード数 */
unsigned char CPMBLOCKREAD(void *FCB, unsigned short *RECORD);

/* CP/M 0x28 ランダムな書き込み（ゼロ埋め）
    FCBのランダムレコード 書き込むレコード番号
    レコードサイズ 128byte固定
    戻り値 0x00:成功 0x01:失敗 */
unsigned char CPMRNDWRITEZ(void *FCB);

/* CP/M 0x2A 日付の獲得 ※MSX-DOSのみ
    date    +0 年（下位）
            +1 年（上位）（1980-2079）
            +2 月
            +3 日
            +4 曜（0=日曜,1=月曜,...,6=土曜）*/
void CPMGETDATE(char *date);

/* CP/M 0x2B 日付の設定 ※MSX-DOSのみ */
void CPMSETDATE(unsigned short year, unsigned char month, unsigned char date);

/* CP/M 0x2C 時刻の獲得 ※MSX-DOSのみ
    time    +0 時
            +1 分
            +2 秒
            +3 1/100秒 */
void CPMGETTIME(char *time);

/* CP/M 0x2D 時刻の設定 ※MSX-DOSのみ
    戻り値 A 00H:成功 FFH:失敗 */
unsigned char CPMSETTIME(unsigned char hour, unsigned char minute, unsigned char second);

/* CP/M 0x2E ベリファイフラグの設定 ※MSX-DOSのみ
    flag 0x00:ベリファイしない 0x01:ベリファイする */
void CPMVERIFY(unsigned char flag);

/* CP/M 0x2F 論理セクタの読み出し ※MSX-DOSのみ
    sect セクタ番号
    quantity セクタ数
    drive A=0 B=1 ...
    DTAに読み出したデータ */
void CPMSECTREAD(unsigned short sect, unsigned char quantity, unsigned char drive);

/* CP/M 0x30 論理セクタの書き込み ※MSX-DOSのみ
    sect セクタ番号
    quantity セクタ数
    drive A=0 B=1 ...
    DTAに書き込むデータ */
void CPMSECTWRTIE(unsigned short sect, unsigned char quantity, unsigned char drive);

#endif
