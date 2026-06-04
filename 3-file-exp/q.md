hedef: dosyadaki column'ların listesini çıkar

entry'leri bir struct[]'a kaydet

basit bir lookup fonksiyonu yaz, prefix ve suffix desteği olsun
-abc% -> abchello
%abc -> helloabc
match'lesin

lookup fonksiyonunda aşamalar
-> çıkarılan column tiplerini listele, basit bir user input ile hangi column üzerinde arama yapmak istediğini sor
-> query term'i sor

lookup sonucunu
[Column1.Name]: Result.1.Value
[Column2.Name]: Result.2.Value
şeklinde listeleyip göster

NOT:
DataRow struct'ı malloc ile dinamik olarak ayarlanmalı, column name'lerine göre ayrı property açılıp okunmamalı. Her column için max 128 byte ayır.

struct DataRow
{
int \*fields;
};
