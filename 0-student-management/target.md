Gönderdiğiniz üç belgedeki (Bellek ve Dosya Sistemi, Struct yapıları, Formatlı Giriş/Çıkış Fonksiyonları) tüm konuları harmanlayan, seni hem zorlayacak hem de bu konularda ustalaşmanı sağlayacak kapsamlı bir proje fikri:

### Proje Adı: **Dinamik Öğrenci ve Log Kayıt Yönetim Sistemi**

Bu proje, bir üniversitenin öğrenci işleri sisteminin çekirdeğini simüle edecektir. Öğrenci verilerini bellekte dinamik olarak tutacak, dosyalarla (hem metin hem de binary) kalıcı hale getirecek ve ekrana düzenli tablolar halinde yazdıracaktır.

#### 1. Projenin İçereceği Konular ve Teknik Beklentiler

**A. Struct ve İşaretçiler (Pointers)**

- [cite_start]**İçiçe Yapılar:** Bir `Tarih` struct'ı (gün, ay, yıl) oluştur ve bunu `Ogrenci` struct'ının (ad, soyad, no, not ortalaması) içinde "Kayıt Tarihi" ve "Doğum Tarihi" olarak kullan[cite: 1152, 1153].
- [cite_start]**Fonksiyonlara Pointer Gönderme:** Öğrenci bilgilerini atamak veya güncellemek için struct'ları fonksiyonlara değer (value) olarak değil, referans (pointer) olarak gönder (örn: `void Ogrenci_Guncelle(struct Ogrenci *ogr)`)[cite: 1207, 1288].

**B. Dinamik Bellek Yönetimi (malloc, realloc, free)**

- Statik bir dizi kullanmak (örneğin `Ogrenci liste[100]`) yasak. [cite_start]Program başladığında hiç öğrenci yoksa bellek ayırma, ilk öğrenci eklendiğinde `malloc` ile tek bir öğrenci için yer ayır[cite: 438].
- [cite_start]Yeni bir öğrenci eklendiğinde dizinin boyutunu `realloc` kullanarak artır[cite: 548, 554].
- [cite_start]Program kapanırken `free` fonksiyonunu kullanarak tüm ayrılan bellekleri temizle ve "memory leak" (bellek sızıntısı) oluşmasını engelle[cite: 507, 557].

**C. Formatlı Giriş / Çıkış ve Tablolama (printf, scanf, sprintf, sscanf)**

- [cite_start]**Tampon Bellek Temizliği:** Kullanıcıdan peş peşe `scanf` ile veri alırken oluşan "Enter" karakteri sorununu çözmek için `while (getchar() != '\n');` mantığını kullan[cite: 1430].
- [cite_start]**Hizalı Tablolar:** Öğrencileri listelerken isimleri sola dayalı (`%-15s`), notları virgülden sonra 2 basamaklı (`%.2f`) ve numaraları 6 haneli (`%06d`) olacak şekilde düzgün bir tablo formatında yazdır[cite: 1339, 1352, 1365].
- [cite_start]**String İşlemleri:** `sprintf` kullanarak öğrencinin bir "özet profil metnini" tek bir string içinde birleştir [cite: 1396] [cite_start]ve `sscanf` ile formatlı bir metin girdisini ayrıştırarak (örn: "Ahmet Yilmaz 12345 3.5") struct içine kaydet[cite: 1409].

**D. Dosya İşlemleri (Text ve Binary)**

- [cite_start]**Binary (İkili) Veritabanı:** Öğrenci verilerini kalıcı olarak saklamak için `kayit.bin` adında bir dosyaya `fwrite` ile topluca yaz ve program açıldığında `fread` ile bu dosyadan okuyarak dinamik belleğe yükle[cite: 752, 771, 790].
- [cite_start]**Text (Metin) Log Dosyası:** Sistemde yapılan her işlemi (örn: "Yeni öğrenci eklendi", "Öğrenci silindi") bir `log.txt` dosyasına `a` (append) modunda `fprintf` kullanarak tarih ve saat bilgisiyle birlikte kaydet[cite: 728, 740].
- [cite_start]**Dosya İçinde Gezinme:** Menüye "Rastgele Öğrenci Oku" seçeneği ekle ve `fseek` kullanarak binary dosyanın ortalarındaki bir öğrencinin kaydına doğrudan atlayarak verisini çek[cite: 687, 690].

---

#### 2. Programın Menü Tasarımı

[cite_start]Program çalıştığında sonsuz bir döngü içinde (`while(1)`) şu menüyü sunmalıdır[cite: 759, 760]:

1.  **Yeni Öğrenci Ekle:** Kullanıcıdan verileri alır, `realloc` ile belleği büyütür, struct içine atar ve Log dosyasına yazar.
2.  [cite_start]**Öğrencileri Listele:** Bellekteki tüm öğrencileri ASCII karakterlerle oluşturulmuş düzgün bir tablo içinde yazdırır[cite: 1448].
3.  [cite_start]**Hızlı Veri Girişi:** `sscanf` mantığını kullanmak için kullanıcıdan tek bir satırda "Ad Soyad No Not" girmesini ister ve ayrıştırır[cite: 1409].
4.  [cite_start]**Veritabanını Yedekle (TXT):** Bellekteki tüm listeyi okunabilir bir `.txt` dosyasına `fprintf` ile tablo şeklinde raporlar[cite: 740].
5.  [cite_start]**Veritabanını Kaydet (BIN):** Diziyi binary dosyaya `fwrite` ile kaydeder[cite: 771].
6.  [cite_start]**Çıkış:** `free` ile bellekleri temizler [cite: 466] ve programı kapatır.

Bu proje, C dilinde orta seviyeden ileri seviyeye geçiş için mükemmel bir sınavdır. Pointers, memory allocation ve file I/O gibi C'nin en güçlü (ve en hata yapılmaya müsait) yapılarını aynı potada eritmeni sağlar.

Projeye başlarken ilk olarak hangi kısımdan (Struct tasarımları, dinamik bellek, dosya işlemleri vs.) başlamak istersin, bu konuda bir taslak veya ipucu oluşturmamı ister misin?
