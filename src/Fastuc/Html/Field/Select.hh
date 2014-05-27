<?hh // strict
namespace Fastuc\Html\Field;

class Select extends \Fastuc\Html\Field
{
	/**
	 * @var \DOMElement
	 */
	private $el;

	/**
	 * @var array
	 */
	private $options;

	public function __construct( $name )
	{
		parent::__construct( $name );

		$this->el = $this->doc->createElement( 'select' );
		$this->el->setAttribute( 'name', $name );
		$this->el->setAttribute( 'id', $name );

		$this->options = array();
		$this->value = null;
	}

	/**
	 * @param mixed $required
	 */
	public function setRequired( $required )
	{
		$this->el->setAttribute( 'required', $required );
	}

	public function setClass( $class )
	{
		$this->el->setAttribute( 'class', $class );
	}

	public function setReadonly( $readonly )
	{
		if( $readonly )
		{
			$this->el->setAttribute( 'readonly', 'readonly' );
		}
		else
		{
			$this->el->removeAttribute( 'readonly' );
		}
	}

	public function setDisabled( $disabled )
	{
		if( $disabled )
		{
			$this->el->setAttribute( 'disabled', 'disabled' );
		}
		else
		{
			$this->el->removeAttribute( 'disabled' );
		}
	}

	public function addOption( $name, $value = null )
	{
		$nameElement = $this->doc->createTextNode( $name );
		$optionElement = $this->doc->createElement( 'option' );
		$optionElement->setAttribute( 'value', $value );
		$optionElement->appendChild( $nameElement );
		$this->el->appendChild( $optionElement );
	}

	public function setOptions( array $options )
	{
		$this->options = options;
	}

	/**
	 * @deprecated Use setValue( $value )
	 */
	public function setSelectedOption( $value )
	{
		$this->setValue( $value );
	}

	/**
	 * @param integer $size
	 */
	public function setSize( $size )
	{
		$this->el->setAttribute( 'size', $size );
	}

	/**
	 * @param mixed $multiple
	 */
	public function setMultiple( $multiple )
	{   
		$this->el->setAttribute( 'multiple' , $multiple );
	}  

	public function __toString()
	{
		foreach( $this->el->childNodes as $option )
		{
			if( $option->getAttribute( 'value' ) == $this->value )
			{
				$option->setAttribute( 'selected', 'selected' );
			}
			else
			{
				$option->removeAttribute( 'selected' );
			}
		}
		return $this->doc->saveXml( $this->el );
	}
}

