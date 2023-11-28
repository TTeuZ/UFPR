package com.marketplace.views;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.marketplace.controllers.ProductController;
import com.marketplace.models.CategoriesList;
import com.marketplace.models.Category;
import com.marketplace.models.Product;
import com.marketplace.enums.PaymentMethodType;
import com.marketplace.enums.StateType;
import com.marketplace.utils.InputReader;

public class CreateProduct extends Interface {
    private ProductController productController;
    private String name;
    private String description;
    private float price;
    private int categoryId;
    private StateType state;
    private boolean donation;
    private HashMap<String, Object> location;
    private ArrayList<PaymentMethodType> payments;
    private ArrayList<String> photos;

    public CreateProduct() {
        this.numberOfOptions = 2;
        this.productController = new ProductController();

        this.name = "";
        this.description = "";
        this.price = 0.0f;
        this.categoryId = 0;
        this.state = StateType.NEW;
        this.donation = false;
        this.location = new HashMap<String, Object>();
        this.payments = new ArrayList<PaymentMethodType>();
        this.photos = new ArrayList<String>();
    }

    public void showOptions() {
        System.out.println("\nProduto");
        System.out.println("1 - Cadastrar");
        System.out.println("2 - Voltar\n");
    }

    public void handleOption(int option) {
        switch (option) {
            case 1:
                this.createProduct();
                break;
            default:
                break;
        }
    }

    private void createProduct() {
        InputReader reader = new InputReader(this.keyboard);
        CategoriesList categoriesList = CategoriesList.getInstance();

        System.out.println("\nCADASTRAR PRODUTO");

        this.name = reader.readString("Nome");
        this.description = reader.readString("Descrição");
        this.price = reader.readFloat("Preço");
        this.donation = reader.readBoolean("Doação");

        System.out.print("Escolha umas das categorias:");
        System.out.println(categoriesList.toString(1));

        Category categoryObj = null;
        while (categoryObj == null) {
            categoryObj = categoriesList.findById(reader.readInt("\nEscolha a Categoria"));

            if (categoryObj == null)
                System.out.println("CATEGORIA INVÁLIDA. Escolha novamente.");
        }
        this.categoryId = categoryObj.getId();

        this.state = reader.readEnum(StateType.class, "Estado");

        System.out.println("\nLOCALIZAÇÃO");

        this.location.put("street", reader.readString("Rua"));
        this.location.put("neighborhood", reader.readString("Bairro"));
        this.location.put("number", reader.readInt("Número"));
        this.location.put("city", reader.readString("Cidade"));
        this.location.put("state", reader.readString("Estado"));

        this.payments.add(reader.readEnum(PaymentMethodType.class, "\nMeio de Pagamento"));

        this.photos.add(reader.readString("Imagem"));

        System.out.println("\nVALIDAR");
        HashMap<String, Object> result;
        result = this.productController.registerProduct(this.name, this.description, this.price, this.categoryId,
                this.state, this.location, this.payments, this.donation, this.photos);

        Product temp = (Product) result.get("product");
        if (temp == null) {
            System.out.println("Não foi possivel cadastrar o produto\n");
            for (Map.Entry<String, Object> entry : result.entrySet())
                System.out.println(entry.getValue());

            return;
        }

        if (this.confirm(temp)) {
            this.productController.confirm(temp);
            this.showOptions();
        }
    }

    private boolean confirm(Product product) {
        InputReader reader = new InputReader(this.keyboard);

        product.showDetails();

        System.err.println("\n");
        return reader.readBoolean("Confirmar");
    }
}