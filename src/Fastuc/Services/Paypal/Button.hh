<?hh // strict
namespace Fastuc\Services\Paypal;

class Button
{
	private string $itemName;
	private $itemNumber;

	private $url;
	private $business;
	private $amount;
	private $currencyCode;

	private $returnUrl;
	private $cancelReturnUrl;
	private $notifyUrl;

	private $custom;
	
	private $representation;

	public function __construct( $itemName, $itemNumber )
	{
		$this->itemName = $itemName;
		$this->itemNumber = $itemNumber;

		$this->url = 'https://www.paypal.com/cgi-bin/webscr';
		$this->representation = '<input type="image" src="https://www.paypalobjects.com/es_ES/ES/i/btn/btn_paynow_LG.gif" border="0" name="submit" alt="PayPal. La forma rápida y segura de pagar en Internet.">';
	}

	public function setUrl( $url )
	{
		$this->url = $url;
	}

	/**
	 * @return string
	 */
	public function getUrl()
	{
		return $this->url;
	}

	public function setRepresentation( $representation )
	{
		$this->representation = $representation;
	}

	public function setBusiness( $business )
	{
		$this->business = $business;
	}

	public function setSandbox( $sandbox )
	{
		if( $sandbox )
		{
			$this->url = 'https://www.sandbox.paypal.com/cgi-bin/webscr';
		}
	}

	public function setAmount( $amount )
	{
		$this->amount = $amount;
	}

	public function setCurrencyCode( $currencyCode )
	{
		$this->currencyCode = $currencyCode;
	}

	public function setCustom( $custom )
	{
		$this->custom = $custom;
	}

	/**
	 * @param string $returnUrl
	 */
	public function setReturnUrl( $returnUrl )
	{
		$this->returnUrl = $returnUrl;
	}

	/**
	 * @return string
	 */
	public function getReturnUrl()
	{
		return $this->returnUrl;
	}
	
	/**
	 * @param string $cancelReturnUrl
	 */
	public function setCancelReturnUrl( $cancelReturnUrl )
	{
		$this->cancelReturnUrl = $cancelReturnUrl;
	}

	/**
	 * @return string
	 */
	public function getCancelReturnUrl()
	{
		return $this->cancelReturnUrl;
	}

	/**
	 * @param string $notifyUrl
	 */
	public function setNotifyUrl( $notifyUrl )
	{
		$this->notifyUrl = $notifyUrl;
	}

	/**
	 * @return string
	 */
	public function getNotifyUrl()
	{
		return $this->notifyUrl;
	}

	public function toHtml()
	{
		return <<<HTML
<form action="{$this->url}" method="post">
<input type="hidden" name="cmd" value="_xclick">
<input type="hidden" name="business" value="{$this->business}">
<input type="hidden" name="lc" value="ES">
<input type="hidden" name="item_name" value="{$this->itemName}">
<input type="hidden" name="item_number" value="{$this->itemNumber}">
<input type="hidden" name="amount" value="{$this->amount}">
<input type="hidden" name="currency_code" value="{$this->currencyCode}">
<input type="hidden" name="button_subtype" value="services">
<input type="hidden" name="no_note" value="1">
<input type="hidden" name="no_shipping" value="1">
<input type="hidden" name="rm" value="1">

<input type="hidden" name="return" value="{$this->returnUrl}">
<input type="hidden" name="cancel_return" value="{$this->cancelReturnUrl}">
<input type="hidden" name="notify_url" value="{$this->notifyUrl}">

<input type="hidden" name="bn" value="PP-BuyNowBF:btn_paynow_LG.gif:NonHosted">
<input type="hidden" name="custom" value="{$this->custom}">
{$this->representation}
<img alt="" border="0" src="https://www.paypalobjects.com/es_ES/i/scr/pixel.gif" width="1" height="1">
</form>
HTML;
	}
}

