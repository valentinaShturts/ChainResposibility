#include <iostream>

using namespace std;

class Receiver
{
	bool BankTransfer;
	bool MoneyTransfer;
	bool PayPalTransfer;
	bool CryptoTransfer;
public:
	Receiver(bool bt, bool mt, bool ppt, bool ct)
	{
		BankTransfer = bt;
		MoneyTransfer = mt;
		PayPalTransfer = ppt;
		CryptoTransfer = ct;
	}
	bool GetBankTransfer()
	{
		return BankTransfer;
	}
	void SetBankTransfer(bool BankTransfer)
	{
		this->BankTransfer = BankTransfer;
	}
	bool GetMoneyTransfer()
	{
		return MoneyTransfer;
	}
	void SetMoneyTransfer(bool MoneyTransfer)
	{
		this->MoneyTransfer = MoneyTransfer;
	}
	bool GetPayPalTransfer()
	{
		return PayPalTransfer;
	}
	void SetPayPalTransfer(bool PayPalTransfer)
	{
		this->PayPalTransfer = PayPalTransfer;
	}
	bool GetCryptoTransfer()
	{
		return CryptoTransfer;
	}
	void SetCryptoTransfer(bool CryptoTransfer)
	{
		this->CryptoTransfer = CryptoTransfer;
	}
};

class PaymentHandler abstract
{
protected:
	PaymentHandler* Successor;
public:
	PaymentHandler* GetHandler()
	{
		return Successor;
	}
	void SetHandler(PaymentHandler* Successor)
	{
		this->Successor = Successor;
	}
	virtual void Handle(Receiver* receiver) abstract;
};

class BankPaymentHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->GetBankTransfer())
			cout << "Bank transfer\n";
		else if (Successor != nullptr)
			Successor->Handle(receiver);
	}
};

// переводы с помощью системы денежных переводов типа WesternUnion или Unistream
class MoneyPaymentHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->GetMoneyTransfer())
			cout << "Transfer through money transfer systems\n";
		else if (Successor != nullptr)
			Successor->Handle(receiver);
	}
};

// система онлайн-платежей PayPal
class PayPalPaymentHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->GetPayPalTransfer())
			cout << "Transfer via paypal\n";
		else if (Successor != nullptr)
			Successor->Handle(receiver);
	}
};

class CryptoPaymentHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->GetCryptoTransfer())
			cout << "Crypto transfer\n";
		else if (Successor != nullptr)
			Successor->Handle(receiver);
	}
};

void Request(PaymentHandler* h, Receiver* receiver)
{
	h->Handle(receiver);
}

int main()
{
	PaymentHandler* bankPaymentHandler = new BankPaymentHandler();
	PaymentHandler* moneyPaymentHandler = new MoneyPaymentHandler();
	PaymentHandler* paypalPaymentHandler = new PayPalPaymentHandler();
	PaymentHandler* cryptoPaymentHandler = new CryptoPaymentHandler();

	bankPaymentHandler->SetHandler(paypalPaymentHandler);
	paypalPaymentHandler->SetHandler(moneyPaymentHandler);
	moneyPaymentHandler->SetHandler(cryptoPaymentHandler);

	Receiver* receiver = new Receiver(false, false, true, false);
	Request(bankPaymentHandler, receiver);
	delete receiver;

	receiver = new Receiver(false, true, false, false);
	Request(bankPaymentHandler, receiver);
	delete receiver;

	receiver = new Receiver(true, false, false, false);
	Request(bankPaymentHandler, receiver);
	delete receiver;

	receiver = new Receiver(false, false, false, true);
	Request(bankPaymentHandler, receiver);
	delete receiver;

	delete bankPaymentHandler;
	delete moneyPaymentHandler;
	delete paypalPaymentHandler;
	delete cryptoPaymentHandler;

	system("pause");
	return 0;
}