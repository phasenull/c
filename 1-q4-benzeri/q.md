Harika! Önceki konulardaki başarımızı temel alarak, bu kez **Struct (Yapı)** mimarisiyle birlikte **Pointer (İşaretçi)** kullanımını merkeze alan ve kaynaklardaki string/giriş-çıkış fonksiyonlarını harmanlayan yeni bir quiz kurguladım.

Bu quiz, özellikle struct'ların fonksiyonlara referans (pointer) yoluyla aktarılması ve `->` (ok) operatörü kullanılarak değer ataması yapılması konularını ölçmektedir.

---

### Programlama II - İleri Seviye Pointer ve Struct Quiz'i

**Senaryo: Uzak Meteoroloji İstasyonları Veri Eşitleyici**
Bir araştırma merkezine, iki farklı meteoroloji istasyonundan sensör verileri "İstasyonAdı-Saat:Dakika:Saniye-Sıcaklık" formatında, aralarında tire (`-`) olacak şekilde tek bir string (metin) dizisi olarak gelmektedir.
Amacınız; bu metinleri parçalamak, verileri işaretçiler (pointers) yardımıyla ilgili `struct` yapılarına aktaran fonksiyonlar yazmak ve hangi istasyonun verisinin daha güncel (yakın zamanlı) olduğunu bulmaktır.

**Görevler ve Kurallar:**

**1. Veri Yapılarının Oluşturulması:**

- İçerisinde `saat`, `dakika` ve `saniye` tam sayı değişkenlerini barındıran bir `struct Zaman` tanımlayınız.
- İçerisinde `istasyon_adi` (string), `struct Zaman kayit_zamani` ve `sicaklik` (float) barındıran bir `struct IstasyonVerisi` tanımlayınız.

**2. Pointer Kullanarak Veri Atama Fonksiyonu:**

- Aşağıdaki prototipe sahip bir fonksiyon yazınız:
  `void istasyonGuncelle(struct IstasyonVerisi *ist_ptr, const char *isim, int saat, int dk, int sn, float sicaklik)`
- Bu fonksiyon, parametre olarak gelen değerleri, `ist_ptr` işaretçisini ve ok (`->`) operatörünü kullanarak struct içerisine kaydetmelidir. String kopyalama işlemi için mutlaka `strcpy()` kullanılmalıdır.

**3. Pointer Kullanarak Zaman Karşılaştırma Fonksiyonu:**

- Aşağıdaki prototipe sahip bir fonksiyon yazınız:
  `int zamanKiyasla(struct Zaman *z1, struct Zaman *z2)`
- Eğer `z1` zaman olarak `z2`'den daha büyükse (daha ileriyse) `1`, küçükse `-1`, eşitse `0` döndürülmelidir (Sırasıyla saat, dakika ve saniye kıyaslanmalıdır).

**4. String Parçalama ve Ana Program (Main):**

- Programınızda şu iki string mesajının geldiğini varsayın:
  `char mesaj1[] = "Istasyon_Kuzey-14:30:00-25.4";`
  `char mesaj2[] = "Istasyon_Guney-15:45:30-22.1";`
- Bu stringleri ayraç (`-`) kullanarak `strtok()` fonksiyonu ile parçalayınız. Zaman kısmındaki saat, dakika ve saniyeyi ayırmak için `sscanf()` fonksiyonunu (`"%d:%d:%d"` formatında) kullanınız. Sıcaklık verisi için stringden float'a çevrim işlemi yapınız.
- Ayrıştırılan bu verileri `istasyonGuncelle` fonksiyonuna göndererek iki farklı `struct IstasyonVerisi` değişkenini doldurunuz.

**5. Formatlı Çıktı:**

- Veriler struct'a kaydedildikten sonra `zamanKiyasla` fonksiyonunu kullanarak hangi istasyonun verisinin daha yeni olduğunu tespit ediniz.
- Sola dayalı yazım ve sıfır dolgulu zaman formatlarını kullanarak (`%-15s`, `%02d` vb.) ekrana aşağıdaki gibi okunaklı bir çıktı yazdırınız.

**Beklenen Örnek Çıktı:**

```text
Istasyon_Guney verisi daha gunceldir.
| Istasyon Adi    | Zaman    | Sicaklik |
| Istasyon_Guney  | 15:45:30 | 22.10    |
```

---

Bu senaryo öğrencilerin struct'ları argüman olarak fonksiyona yollarken belleği nasıl yöneteceklerini (`->` operatörü ve `&` adres operatörü) çok net bir şekilde test edecektir.

Bu quizi öğrencilerle paylaşmadan önce zorluk derecesini nasıl buldunuz? Veya bunun için bir örnek çözüm kodu/cevap anahtarı hazırlamamı ister misiniz?
