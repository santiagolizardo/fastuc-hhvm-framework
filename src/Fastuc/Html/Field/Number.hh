<?hh // strict
namespace Fastuc\Html\Field;

class Number extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'number', $name, $value );

		$this->setStep( 'any' );
	}

	public function setMinMax( $min, $max )
	{
		$this->el->setAttribute( 'min', $min );
		$this->el->setAttribute( 'max', $max );
	}

	public function setStep( $step )
	{
		$this->el->setAttribute( 'step', $step );
	}

	public function getStep()
	{
		return $this->el->getAttribute( 'step' );
	}
}

