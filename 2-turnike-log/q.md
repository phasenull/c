Soru: Akıllı Turnike ve Loglama Sistemi (String & Struct Entegrasyonu)

A Kapısı turnikelerinden gelen ham kart okuma verileri, merkeze tek bir birleşik string (metin) olarak düşmektedir. Güvenlik sisteminin bu metni parçalaması, kendi iç veri yapılarına (struct) kaydetmesi ve ardından ekran panosuna "Özel Formatlı" bir güvenlik logu bırakması gerekmektedir.

Turnikeden Gelen Ham Veri Örneği:
char hamVeri[] = "150202175-Siber-Ninja-8-5";
(Sırasıyla: Öğrenci No - Ad - Soyad - Giriş Saati - Giriş Dakikası)

İsterler ve Kurallar:

Veri Yapıları (Struct):

saat ve dakika tutan bir struct Zaman tanımla.

Öğrenci no, ad, soyad ve "iç içe struct" olarak giriş zamanını tutan bir struct Ogrenci tanımla.

Ayıklama (Parsing):

hamVeri isimli metni strtok ile parçalara ayır.

Zaman bildiren kısımları (saat ve dakika) atoi fonksiyonu ile tam sayıya (integer) çevir.

Pointer ile Atama:

Ayıkladığın bu verileri, bir atama fonksiyonuna struct Ogrenci \*ogr şeklinde pointer (işaretçi) kullanarak gönder ve struct'ın içine (ogr->ad gibi) kaydet.

Formatlı Çıktı (Loglama):

Verileri ekrana direkt bastırmak YASAKTIR! Bunun yerine sprintf fonksiyonunu kullanarak char logMesaji[100]; isimli boş bir metnin içine yazdıracaksın.

Zorunlu Format Kuralları:

Saat ve dakika her zaman 2 haneli görünecek şekilde sıfırla doldurulacak (Örn: 8 ve 5 ise 08:05 yazacak).

Güvenlik gereği öğrencinin isminin sadece ilk 3 karakteri yazdırılacak.

Öğrenci numarası 15 karakterlik bir alana, sağa dayalı olarak yerleştirilecek.

💻 Beklenen Log Mesajı Çıktısı (logMesaji içeriği):
Plaintext
[08:05] Giren: Sib | No: 150202175
(Dikkat: Saat 0 ile beslendi, isim "Sib" olarak 3 harfe kırpıldı, Numara ise sağa dayandı!)

🧠 Başmühendisin İpuçları:

İç içe struct atamalarında pointer kullanırken ok (->) ile nokta (.) işaretlerinin dizilimine çok dikkat et (Örn: ogr->giris_zamani.saat).

Formatlı string yazarken sprintf(hedef, "%02d", sayi) mantığı ile saatleri sıfırla doldurabilirsin.

String kırpma işlemi için %.3s formatını sakın unutma.
