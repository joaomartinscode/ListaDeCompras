# ListaDeCompras

**ListaDeCompras** is a C-based program designed for managing shopping lists as part of a university project on **Algorithms and Data Structures**. The program implements the concept of Abstract Data Types (ADT) to manage a collection of products and shopping lists. The user can perform operations like adding, removing, updating products, and managing shopping lists, including marking products as purchased.

## Features

- **Product Management**: Add, remove, and update products with attributes like name, type, price, and store.
- **Product Search**: Search for products by name, part of name, or type. Handle cases with multiple matches or no matches.
- **Shopping List Management**: Create, delete, and rename shopping lists. Associate products with quantities and purchase status.
- **Product Operations**: Insert, remove, and update product information, including marking as purchased with price and store details.
- **Dynamic Array Management**: Uses dynamically allocated arrays for managing data.

## Operations

### Product Operations:
- **Add Product**: Create a product with a unique name, type, price, and store.
- **Remove Product**: Delete a product from the database.
- **Update Product**: Change the product’s name or details (e.g., price or store).
- **Search Products**: Find products by full or partial name, and by type.
  
### Shopping List Operations:
- **Create Shopping List**: Create a list with a unique name.
- **Add Product to List**: Insert a product into a shopping list with quantity.
- **Remove Product from List**: Delete a product from a shopping list.
- **Display Shopping List**: List all products with their details and purchase status.
- **Mark Product as Purchased**: Mark a product as purchased and update its price and store details.
- **Unmark All Purchased Products**: Reset the purchased status for all products in a list.

## Technologies

- **C Programming Language**
- Abstract Data Types (ADT)
- Dynamic Arrays

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/joaomartinscode/ListaDeCompras.git
   ```

2. Navigate to the project folder:
   ```bash
   cd ListaDeCompras
   ```

3. Compile the project:
   ```bash
   gcc -o ListaDeCompras main.c BDlista.c BDproduto.c
   ```

4. Run the application:
   ```bash
   ./ListaDeCompras
   ```
