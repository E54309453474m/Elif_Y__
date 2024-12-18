# Elif_Y__
# KOD

Kodun başında typedef struck olarak odayı ve oyuncuyu tanımladım. 
Bir odada sırası ile odanın tanımı, odanın içindeki öğeleri ve canavarları, öğelerin ve canavarların sayısı ve diğer oda ile bağlantısı hangi yönde olduğu bilinmesi için yönler verilmiştir.
Oyuncuda sırası ile sağlık, güç, envanterinin içeriği ve envanterindeki öğe sayısı verilmiştir.

"create_room" methodu ile odanın array char tanımını yapar, odalara otomatik olarak sıfır öğe ve canavar düşürür ve yönleri de null olarak atar.
"coonect_rooms" methodu aldığı iki oda ve yçn bilgisi ile birbirlerini bağlar. Böylece ilk odadan ikinci odaya left komutu ile gidilirken ikinci odadan birinci odaya right komutu ile dönülebilir.
"add_item_and_creature" kodu eğer odaya bir öğe veya canavar eklenirse hem kendi array'lerine eklenecek hem de sayıları bir artacak şeklinde yazılmıştır.
Bu üç method ile odalar kendilerine öz ve birbirine bağlı şekilde oluşturulur.

"move" methodu oyuncudan aldığı yön ile çalışır. Bu method oyuncunun anlık bulunduğu odadan denilen yönde bir oda varsa o odaya gitme eğlemini gerçekleştirir. Eğer verilen yönde bir oda yoksa o yönde gidilemeyceği dönüşünü verir.
"look" methodu bulunduğu odaya yöneliktir. Odanın tanımını söyler sonra odada öğe olup olmadığına bakar. Odada öğe varsa ayrı bir satırda bunu da söyler. En son odada bir canavar var mı diye bakar aynı şekilde canavar varsa söyler yoksa hiçbir şey demez.
"inventory" fonksiyonu oyuncunun anlık envanter bilgisini söyler.
"pickup" fonksiyonu önce envanterşnde boş yer olup olmadığına bakar. Envanter dolu ise pickup komutunu gerçekleştirmez ve menüye döner. Envanter boş ise odadaki öğeyi envantere koyar ve odanın bilgilerini değiştirir böylece bir öğe iki farklı yerde bulunmaz.
"attack" komutu oyuncu ile canavarı karşılaştırır ve kimin kazandığına karar verir. Eğer oyuncu yenilirse yenildiğini söyler ve oyun kapanır, Kazanırsa kazandığını ve ne kadar can kaybettiğiini söyleyip menüye geri döner.
"load_game" ve "save_game" komutları oyunun anlık bilgileri ile ilgilidir. "save_game" komutu oyuncunun kaldığı odayı ve oyuncunun durumu hakkındaki bilgileri toplar. "load_game" ise bu toplanan bilgileri alır.
Main methodda odalar tanımlanır içlerine canavarlar ya da öğeler yerleştirilir, diğer odanın yön ile ilgili bilgi verilir. Oyuncunun başlangıç durumu verilir(Hangi odada olduğı, sağlığı, gücü, envanter durumu verilir.). Menü sekmesini oluşturur ve oyuncuya ne yapmak istediğini sorar. Oyuncu exit komutunu seçerse oyunu kapatır başka komutları seçerse o methodlara yönlendirir.

# Oyun

Oyunda altı farklı oda, iki farklı öğe ve iki farklı canavar var. Oyuncunun oyunun başında 50 canı, 30 vurma gücü ve boş bir envanteri var.
Odalar sırası ile 1 - There are two torches illuminating this room, 2 - A bright room with a glowing sword, 3 - A  dark narrow corridor, 4 - There is a cyclop in this room, 5 - A bright room with a silver locket, 6 - There is a kerberos in this room, diyerek tanımlanıyor.
Odalar arasında yer değiştirmek ‘move <direction>komutu ile yapılır. Bu odalara geri dönülmek istenirse oyuncunun tek yapması gereken move ve nasıl geldiyse zıttı yöne komut vermektir.

Bu oyunda toplam iki çeşit canavar var: Cyclop ve Kerberos. Her canavarın kendine özgü bir sağlığı ve gücü var. Bu canavarların sırasıyla şöyledir: 1 - Cyclop = Sağlık 20, Güç 10, 2 - Kerberos = Sağlık 40, Güç 40.
Oyuncu canavarlar ile karşılaştıktan sonra ‘attack’ komutunu seçerse karşılaştığı canavarın gücü kadar hasar alır ve sağlığı sıfırın altına düşerse oyun yenildiğini söyler ve kapanır. Eğer sıfırın altına düşmezse ve oyuncunun gücü canavarın sağlığını aşarsa oyuncunun yendiğini söyler ve odadaki canavar yok olur.
Kerberos'u yenmek için öğeleri alması gerekir.Eğer zamanında öğeleri almazsa Kerberos'un karşısında attack komutu verirse ölür ve oyun kapanır.

Oyunda kaydetme, çıkış yapma, kaydedilen oyunları gösterme ve kaydedilen oyunu tekrardan yükleme komutları bulunur. Bu komutlar sırası ile ‘save’, ‘exit’, ‘list’ ve ’load’ olarak bulunur. Oyuncunun oyundan çıkması iki farklı şekilde gerçekleşir. Birinci şekli exit komutunu verip oyundan çıkmak iken ikinci şekli oyuncunun karşılaştığı canavara yenilmesidir.
