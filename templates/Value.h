template <class T>
class Value {
public:
  Value();
  Value<T>(T x);
  T getValue();
  void setValue(T value);

private:
  T value;
};

template <class T>
Value<T>::(T value) {
  this -> value = value;
}

template <class T>
T Value<T>::getValue() {
  return this -> value;
}
