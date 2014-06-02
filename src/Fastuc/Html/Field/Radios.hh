<?hh // strict
namespace Fastuc\Html\Field;

class Radios extends \Fastuc\Html\Field
{
	protected $name;
	protected $radios;
	protected $checkedRadioValue;

	public function __construct( $name )
	{
		$this->name = $name;
		$this->radios = array();
		$this->checkedRadioValue = null;
	}

	public function addRadio( $value, $label )
	{
		$radio = new Radio( $this->name, $value );
		$radio->setLabel( $label );
		$this->radios[] = $radio;
	}

	public function setCheckedRadio( $value )
	{
		$this->checkedRadioValue = $value;
	}

	public function __toString()
	{
		$html = '';
		foreach( $this->radios as $radio )
		{
			$radio->setChecked( $radio->getValue() == $this->checkedRadioValue );
			$html .= strval($radio);
		}
		return $html;
	}
}

