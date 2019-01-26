import javax.persistence.*;
import java.util.List;

@Entity
public class Category {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int CategoryID;

    private String name;

    @OneToMany(mappedBy = "category")
    List<Product> products;

    public Category() {

    }

    public Category(String name) {
        this.name = name;
    }

    public List<Product> getProducts() {
        return products;
    }

    public String getName() {
        return name;
    }
}

