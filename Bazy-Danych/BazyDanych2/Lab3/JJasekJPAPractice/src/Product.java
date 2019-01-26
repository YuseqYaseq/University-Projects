
import javax.persistence.*;
import java.util.Set;


@Entity
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int dbID;

    @Column(name = "ProductName")
    private String productName;

    @Column(name = "UnitsOnStock")
    private int unitsOnStock;

    @ManyToOne
    private Supplier supplier;

    @ManyToOne
    private Category category;

    @ManyToMany
    private Set<Invoice> invoices;

    public void setCategory(Category category) {
        this.category = category;
    }

    public Category getCategory() {
        return category;
    }

    public Product() {

    }

    public Product(String productName, int unitsOnStock) {
        this.productName = productName;
        this.unitsOnStock = unitsOnStock;
    }

    public void setSupplier(Supplier supplier) {
        this.supplier = supplier;
    }

    public void addInvoice(Invoice invoice) {
        invoices.add(invoice);
    }
}
